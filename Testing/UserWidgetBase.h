// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTING_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Widget")
	void UpdateData();
};
