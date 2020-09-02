// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "UtilityFunctions.generated.h"

UCLASS()
class TESTING_API UUtilityFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Append String", CompactNodeTitle = "Append", Keywords = "String append", CommutativeAssociativeBinaryOperator = "true"), Category = "Utilities|Strings")
	static FString AppendString(FString A, FString B);
};
