// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "UserWidgetBase.h"
#include "Components/ActorComponent.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintOnItemAdded, AInventoryItem*, Item);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UInventory : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Item Added"), Category = "Inventory")
	FBlueprintOnItemAdded BlueprintOnItemAdded;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<AInventoryItem*> Items;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	class TSubclassOf<UUserWidgetBase> StartingWidgetDisplay;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	UUserWidgetBase* WidgetDisplay;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	bool Visible;
	
public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(AActor* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInventoryItem(AInventoryItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<AInventoryItem*> GetItems() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DisplayWidget();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void HideWidget();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsDisplayed() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleWidget();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUserWidgetBase* GetWidget();
};
