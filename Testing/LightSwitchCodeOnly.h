// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LightSwitchCodeOnly.generated.h"

UCLASS()
class TESTING_API ALightSwitchCodeOnly : public AActor
{
	GENERATED_BODY()
	
public:	

		/* Point light component */
		UPROPERTY(VisibleAnywhere, Category = "Switch Components")
			class UPointLightComponent* PointLight1;

		/* Sphere component */
		UPROPERTY(VisibleAnywhere, Category = "Switch Components")
			class USphereComponent* Sphere1;

		// Sets default values for this actor's properties
		ALightSwitchCodeOnly();

		/* Called when something enters the sphere component */
		UFUNCTION()
			void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		/* Called when something leaves the sphere component */
		UFUNCTION()
			void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		/* Toggles the light component's visibility */
		UFUNCTION()
			void ToggleLight() const;

		/* The desired intensity for the light */
		UPROPERTY(VisibleAnywhere, Category = "Switch Variables")
			float DesiredIntensity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
