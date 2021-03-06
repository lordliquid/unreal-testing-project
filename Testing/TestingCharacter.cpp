// Copyright Epic Games, Inc. All Rights Reserved.

// ReSharper disable CppMemberFunctionMayBeConst

#include "TestingCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ItemBase.h"
#include "MenuHUD.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

//////////////////////////////////////////////////////////////////////////
// ATestingCharacter

ATestingCharacter::ATestingCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	SelectDistance = 100.0f;
	SelectHeight = 65.0f;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"), false);
}

void ATestingCharacter::Tick(float delta)
{
	Super::Tick(delta);

	UpdateSelectedItem();
}

// 	// const FVector ActorForward = GetActorForwardVector();
// 	// const FVector WorldLocation = GetActorLocation();
// 	//
// 	// const FVector Forward = UKismetMathLibrary::Multiply_VectorFloat(ActorForward, SelectDistance);
// 	//
// 	// FVector Distance;
// 	//
// 	// Distance.X = WorldLocation.X;
// 	// Distance.Y = WorldLocation.Y;
// 	// Distance.Z = WorldLocation.Z + SelectHeight;
// 	//
// 	// TArray<struct FHitResult> hits;
// 	// hits.Reset();
// 	//
// 	// UWorld* World = GetWorld();
// 	// static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
//
// 	//FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
// 	//TraceParams.bTraceAsyncScene = true;
// 	//TraceParams.bReturnPhysicalMaterial = true;
//
// 	//bool GotHit = World->LineTraceMultiByChannel(hits, Distance, Forward, (ECollisionChannel)3, TraceParams);
// 	//hits.Reset();
//
// 	// UKismetSystemLibrary::LineTraceMulti(this, Distance, Forward, (ECollisionChannel) 3, true, )
// }

//////////////////////////////////////////////////////////////////////////
// Input

void ATestingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATestingCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestingCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATestingCharacter::TurnAtRate);
	
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATestingCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATestingCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATestingCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATestingCharacter::OnResetVR);
	PlayerInputComponent->BindAction("OpenMenu", IE_Pressed, this, &ATestingCharacter::OpenMenu);

	// Selected Item Bindings
	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &ATestingCharacter::UseItem);
}

void ATestingCharacter::OpenMenu()
{
	if (AMenuHUD* MenuHUD = Cast<AMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		MenuHUD->ShowMenu();
	}
}

FHitResult ATestingCharacter::GetSelectedHit()
{
	const FVector WorldLocation = FollowCamera->GetComponentTransform().GetLocation();
	const FRotator WorldRotation = FollowCamera->GetComponentTransform().GetRotation().Rotator();
	const FVector ForwardVector = WorldRotation.Vector();
	const FVector VectorOffset = UKismetMathLibrary::Multiply_VectorFloat(ForwardVector, 1500.f);
	const FVector EndVector = UKismetMathLibrary::Add_Vector4Vector4(WorldLocation, VectorOffset);
	const TArray<AActor*> Ignored;

	FHitResult HitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), WorldLocation, EndVector, TraceTypeQuery3, true, Ignored, EDrawDebugTrace::None, HitResult, true, FLinearColor::Green, FLinearColor::Green, .1f);

	return HitResult;
}

void ATestingCharacter::UpdateSelectedItem()
{
	AActor* HitActor = GetSelectedHit().GetActor();

	if (HitActor)
	{
		if (SelectedItem != HitActor)
		{
			if (HitActor->GetClass()->ImplementsInterface(USelectable::StaticClass()))
			{
				ISelectable* Selectable = Cast<ISelectable>(HitActor);
				Selectable->Execute_SelectItem(HitActor);
				Selectable->Execute_HighlightItem(HitActor);
				Selectable->SelectItem_Implementation();
				Selectable->HighlightItem_Implementation();
			}
			SelectedItemChanged(SelectedItem, HitActor);
			SelectedItem = HitActor;
		}
	}
	else
	{
		SelectedItem = nullptr;
	}
}

UResource* ATestingCharacter::GetResource()
{
	return Cast<UResource>(GetSelectedHit().GetActor());
}

AResourceBase* ATestingCharacter::GetResourceBase()
{
	return Cast<AResourceBase>(GetSelectedHit().GetActor());
}

void ATestingCharacter::UseItem()
{
	if (SelectedItem)
	{
		AItemBase* ItemBase = Cast<AItemBase>(SelectedItem);
		if (ItemBase)
		{
			ItemBase->UseItem(this);
		}
	}
}

void ATestingCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATestingCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATestingCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ATestingCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATestingCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATestingCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATestingCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

