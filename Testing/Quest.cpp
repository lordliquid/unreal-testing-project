// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

UQuestStatus::UQuestStatus()
{
}

void UQuestStatus::BeginPlay()
{
}

// Called every frame
void UQuestStatus::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UQuestStatus::UpdateQuests(USM_InputAtom* QuestActivity)
{
    // Update the master list of everything we've ever done.
    QuestActivities.Add(QuestActivity);

    // Update individual quests (if they care about this activity) and see if they are complete.
    for (int32 i = QuestList.Num() - 1; i >= 0; --i)
    {
        if (QuestList[i].UpdateQuest(this, QuestActivity))
        {
            UE_LOG(LogTemp, Warning, TEXT("Quest \"%s\" completed: %s"),
                *QuestList[i].Quest->QuestName.ToString(),
                (QuestList[i].QuestProgress == EQuestCompletion::EQC_Succeeded) ? TEXT("Success") : TEXT("Failure"));
        }
    }
}
