// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatVariable.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UFloatVariable : public UActorComponent
{
	GENERATED_BODY()

public:	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintOnActivated, float, NewValue);

	// Sets default values for this component's properties
	UFloatVariable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetValue, Category = "Variable")
		float Value;

	UFUNCTION(BlueprintSetter, Category = "Variable")
		void SetValue(float NewValue);

	UFUNCTION()
		void OnPayloadActivated(float NewValue) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnValueChanged"))
		FBlueprintOnActivated BlueprintOnActivated;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
};
