// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "TestingGameMode.generated.h"

UCLASS(minimalapi)
class ATestingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestingGameMode();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};



