// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatVariable.h"

// Sets default values for this component's properties
UFloatVariable::UFloatVariable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Value = 1.0f;
	// ...
}


// Called when the game starts
void UFloatVariable::BeginPlay()
{
	Super::BeginPlay();
	//OnComponentActivated.AddDynamic(this, &UFloatVariable::OnPayloadActivated);
	// ...
	
}

// Called every frame
void UFloatVariable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFloatVariable::SetValue(float NewValue)
{
	if (Value != NewValue)
	{
		Value = NewValue;
		BlueprintOnActivated.Broadcast(Value);
	}
}

void UFloatVariable::OnPayloadActivated(float NewValue) const
{
	BlueprintOnActivated.Broadcast(NewValue);
}

void UFloatVariable::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}