// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Components/SphereComponent.h"
AMineItem::AMineItem()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	Collision->InitSphereRadius(Radius);
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);
	Delay = 5.0f;
	Radius = 300.0f;
	Damage = 30;
	ItemType = "Mine";
}
void AMineItem::ActivateItem(AActor* Activator)
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explode, Delay, false);
}

void AMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;
	Collision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				2.0f,
				FColor::Red,
				FString::Printf(TEXT("Player damaged %d by MineItem"), Damage));
		}
	}
	DestroyItem();
}
