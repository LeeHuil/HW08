// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20;
	ItemType = "Posion";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Red,
			FString::Printf(TEXT("Player gained %d HP"), HealAmount)
		);
		DestroyItem();
	}
}