// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "RollABall/Items/RollABallItemBase.h"

void ARollABallGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollABallItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();
}

void ARollABallGameModeBase::UpdateItemText()
{
}

void ARollABallGameModeBase::ItemCollected()
{
	ItemsCollected++;
}
