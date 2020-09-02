// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraActivatorPad.h"



#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/TriggerVolume.h"

// Sets default values
ACameraActivatorPad::ACameraActivatorPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
    RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(10.0f));
	BoxComponent->SetCollisionProfileName(TEXT("Pawn"));
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	// SphereVisual->SetupAttachment(RootComponent);
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	// if (SphereVisualAsset.Succeeded())
	// {
	// 	SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
	// 	SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	// 	SphereVisual->SetWorldScale3D(FVector(0.8f));
	// }

    // ATriggerVolume* TriggerVolume = CreateDefaultSubobject<ATriggerVolume>(TEXT("TriggerVolume"));
}

// Called when the game starts or when spawned
void ACameraActivatorPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraActivatorPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

