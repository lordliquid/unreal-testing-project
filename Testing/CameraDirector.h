// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class TESTING_API ACameraDirector : public AActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere)
    AActor* PreviousViewTarget;

    UPROPERTY(EditAnywhere)
    bool bEnabled = false;

    UPROPERTY(EditAnywhere)
    float SmoothBlendTime = 0.75f;

    UPROPERTY(EditAnywhere)
    float TimeBetweenCameraChanges = 2.0f;

public:
    // Sets default values for this actor's properties
    ACameraDirector();

    UFUNCTION(BlueprintCallable)
    void Enable();

    UFUNCTION(BlueprintCallable)
    void Disable();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    AActor* CameraOne;

    UPROPERTY(EditAnywhere)
    AActor* CameraTwo;

    float TimeToNextCameraChange;
};
