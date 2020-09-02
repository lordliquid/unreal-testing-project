// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API AInventoryItem : public AActor, public IItem
{
	GENERATED_BODY()
	
	AInventoryItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPROPERTY(VisibleAnywhere, Category="Inventory Item")
	AActor* Item;

	UFUNCTION(BlueprintCallable, Category="Inventory Item")
	FString GetItemName() const;
};
