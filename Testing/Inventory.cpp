// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Visible = false;
	// WidgetDisplay = CreateWidget<UUserWidget>(GetWorld(), StartingWidgetDisplay);
	// ...
}

// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	WidgetDisplay = CreateWidget<UUserWidgetBase>(GetWorld(), StartingWidgetDisplay);
}

// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventory::AddItem(AActor* Item)
{
	AInventoryItem* InventoryItem = NewObject<AInventoryItem>(Item);
	InventoryItem->Item = Item;
	return AddInventoryItem(InventoryItem);
}

bool UInventory::AddInventoryItem(AInventoryItem* Item)
{
	const int previousSize = Items.Num();
	const int newSize = Items.Add(Item) + 1;
	BlueprintOnItemAdded.Broadcast(Item);
	return previousSize == newSize;
}

TArray<AInventoryItem*> UInventory::GetItems() const
{
	return Items;
}

void UInventory::DisplayWidget()
{
	if (!Visible)
	{
		Visible = true;
		GetWidget()->AddToViewport();
	}
}

void UInventory::HideWidget()
{
	if (Visible)
	{
		Visible = false;
		GetWidget()->RemoveFromViewport();
	}
}

bool UInventory::IsDisplayed() const
{
	return Visible;
}

void UInventory::ToggleWidget()
{
	if (IsDisplayed())
	{
		HideWidget();
	}
	else
	{
		DisplayWidget();
	}
}

UUserWidgetBase* UInventory::GetWidget()
{
	if (WidgetDisplay == nullptr)
	{
		WidgetDisplay =  CreateWidget<UUserWidgetBase>(GetWorld(), StartingWidgetDisplay);
	}
	
	return WidgetDisplay;
}


