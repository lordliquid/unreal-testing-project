// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inventory.h"
#include "Resource.h"
#include "ResourceBase.h"
#include "TestingCharacter.generated.h"

class AMenuHUD;
UCLASS(config=Game)
class ATestingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	class UInventory* Inventory;
	
public:
	ATestingCharacter();
	virtual void Tick(float delta) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	float SelectDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	float SelectHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing Character", meta = (AllowPrivateAccess = "true"))
	AActor* SelectedItem;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// virtual void Tick(float delta) override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintCallable)
	void OpenMenu();

	UFUNCTION(BlueprintCallable)
	FHitResult GetSelectedHit();
	
	UFUNCTION(BlueprintImplementableEvent)
	void SelectedItemChanged(AActor* PreviousActor, AActor* NewActor);
	
	UFUNCTION(BlueprintCallable)
	void UpdateSelectedItem();

	UFUNCTION(BlueprintCallable)
	UResource* GetResource();

	UFUNCTION(BlueprintCallable)
	AResourceBase* GetResourceBase();

	UFUNCTION(BlueprintCallable)
	void UseItem();
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

