// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CameraDirector.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraActivatorPad.generated.h"

UCLASS()
class TESTING_API ACameraActivatorPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraActivatorPad();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraDirector* CameraDirector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
