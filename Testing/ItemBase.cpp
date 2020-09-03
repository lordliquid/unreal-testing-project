// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Name = FString("ItemBase");
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::HighlightItem_Implementation()
{
	TInlineComponentArray<UActorComponent*> PrimComponents;
	this->GetComponents(PrimComponents);

	// for (UActorComponent* PrimComponent : PrimComponents)
	// {
	// 	GetMeshPrimComponent
	// }

	TArray<AActor*> Actors;
	GetAttachedActors(Actors);
	for (AActor* Actor : Actors)
	{
		UE_LOG(LogTemp, Log, TEXT("Hi, I'm %s"), *Actor->GetName());
	}
}

