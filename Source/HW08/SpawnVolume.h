// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
UCLASS()
class HW08_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();
	UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category="Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Spawning")
	UDataTable* ItemDataTable;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomItem();

	FVector GetRandomPointInVolum() const;
	void SpawnItem(TSubclassOf<AActor>ItemClass);
	FItemSpawnRow* GetRandomItem() const;
};
