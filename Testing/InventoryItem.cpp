// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

AInventoryItem::AInventoryItem(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Item = nullptr;
}

FString AInventoryItem::GetItemName() const
{
    if (Item == nullptr)
    {
        return FString(TEXT("NULL"));
    }
    return Item->GetFName().ToString();
}
