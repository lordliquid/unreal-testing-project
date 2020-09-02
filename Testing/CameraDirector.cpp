// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACameraDirector::Enable()
{
	if (PreviousViewTarget == nullptr)
	{
		PreviousViewTarget = UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget();
	}

	bEnabled = true;
}

void ACameraDirector::Disable()
{
	if (PreviousViewTarget != nullptr)
	{
		UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(PreviousViewTarget, SmoothBlendTime);
		PreviousViewTarget = nullptr;
	}

	bEnabled = false;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEnabled)
	{
		TimeToNextCameraChange -= DeltaTime;

		if (TimeToNextCameraChange <= 0.0f)
		{
			TimeToNextCameraChange += TimeBetweenCameraChanges;

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

			if (PlayerController)
			{
				if ((PlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
				{
					// Cut instantly to camera one.
					PlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
				}
			
				else if ((PlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
				{
					// Blend smoothly to camera two.
					PlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
				}
			}
		}
	}
}

