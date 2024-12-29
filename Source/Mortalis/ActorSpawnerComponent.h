// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NavMesh/RecastNavMesh.h"

#include "ActorSpawnerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORTALIS_API UActorSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorSpawnerComponent();

	// Spawner Configuration
	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration", meta = (DeterminesOutputType = "ObjClass"))
	void AddActorToSpawnPool(TSubclassOf<class UObject> Actor);

	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration")
	void SetActorSpawnPool(TArray<TSubclassOf<class UObject>> Actors);

	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration")
	void EnablePeriodicSpawn(float IntervalInSeconds, int32 Waves);

	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration")
	void DisablePeriodicSpawn();

	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration")
	void EnableNavMeshPositionSelection();

	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration")
	void DisableNavMeshPositionSelection();

	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration")
	void SetActorSpawnCount(int32 SpawnCount);

	UFUNCTION(BlueprintCallable, Category="Spawn/Configuration")
	void SetSpawnRadius(float Radius);

	// Spawner Actions
	UFUNCTION(BlueprintCallable, Category="Spawn/Action")
	void Spawn();

	UFUNCTION(BlueprintCallable, Category="Spawn/Action")
	int32 GetNumberOfWavesSpawned() const;
	
	UFUNCTION(BlueprintCallable, Category="Spawn/Action")
	int32 GetNumberOfWavesLeft() const;

	UFUNCTION(BlueprintCallable, Category="Spawn/Action")
	float GetTimeToNextSpawn() const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SpawnWithNavMeshSelectionEnabled();
	void SpawnWithStaticPosition();

	bool ShouldSpawnActors(float DeltaTime);

	int32 SelectRandomActor() const;

private:
	TArray<TSubclassOf<class UObject>> ActorsSpawnPool;
	TArray<AActor*> SpawnedActors = {};

	FVector RootLocation = {};

	bool bPeriodicSpawnEnabled = false;
	bool bNavMeshPositionSelectionEnabled = false;

	float SpawnIntervalInSeconds = 10.0f;
	float TimeSinceLastSpawn = 0.0f;
	float SpawnRadius = 0.0f;

	int32 WavesToSpawn = 0;
	int32 WavesSpawned = 0;
	int32 ActorsSpawnCount = 0;
};
