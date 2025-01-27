// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerComponent.h"
#include "GameManager.h"
#include "CoreGlobals.h"
#include "Engine/World.h"
#include "HAL/Platform.h"

#include "Logging/LogMacros.h"
#include "Logging/StructuredLog.h"
#include "NavMesh/RecastNavMesh.h"
#include "NavigationSystem.h"
#include "UObject/Object.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UActorSpawnerComponent::UActorSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	RootLocation = GetOwner()->GetRootComponent()->GetComponentLocation();
}


void UActorSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	while (ShouldSpawnActors(DeltaTime))
	{
		Spawn();
	}
}

void UActorSpawnerComponent::AddActorToSpawnPool(TSubclassOf<AEnemyBase> Actor)
{
	ActorsSpawnPool.Add(Actor);
}

void UActorSpawnerComponent::SetActorSpawnPool(TArray<TSubclassOf<AEnemyBase>> Actors)
{
	if (Actors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting actors spawn pool to an empty array."));
	}

	ActorsSpawnPool = MoveTemp(Actors);
}

void UActorSpawnerComponent::EnablePeriodicSpawn(const float IntervalInSeconds, const int32 Waves)
{
	if (IntervalInSeconds <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn interval must be greater than 0."));
	}

	SpawnIntervalInSeconds = IntervalInSeconds;

	if (Waves <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn interval should be greater than 0."));
	}

	WavesToSpawn = Waves;
	bPeriodicSpawnEnabled = true;
}

void UActorSpawnerComponent::DisablePeriodicSpawn()
{
	// TODO: check if tick should be disabled for performance improvement
	bPeriodicSpawnEnabled = false;
}

void UActorSpawnerComponent::EnableNavMeshPositionSelection()
{
	bNavMeshPositionSelectionEnabled = true;
}

void UActorSpawnerComponent::DisableNavMeshPositionSelection()
{
	bNavMeshPositionSelectionEnabled = false;
}

void UActorSpawnerComponent::SetActorSpawnCount(const int32 SpawnCount)
{
	if (SpawnCount < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting actors spawn count to 0."));
	}

	ActorsSpawnCount = SpawnCount;
}

void UActorSpawnerComponent::SetSpawnRadius(const float Radius)
{
	if (Radius < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn radius must be greater or equal 0."));
		return;
	}

	SpawnRadius = Radius;
}

void UActorSpawnerComponent::Spawn()
{
	if(bNavMeshPositionSelectionEnabled)
	{
		SpawnWithNavMeshSelectionEnabled();
	}
	else
	{
		SpawnWithStaticPosition();
	}

	++WavesSpawned;

	if (WavesSpawned >= WavesToSpawn)
	{
		DisablePeriodicSpawn();
	}
}

void UActorSpawnerComponent::SpawnWithNavMeshSelectionEnabled()
{
	auto NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	
	FNavLocation SelectedSpawnLocation;
	for (int32 i = 0; i < ActorsSpawnCount; i++)
	{
		auto Result = NavSystem->GetRandomPointInNavigableRadius(RootLocation, SpawnRadius, SelectedSpawnLocation);
		if (not Result)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to select random point in nav mesh, can't spawn entity."));
			continue;
		}

		// TODO: change hardcode for half of target height
		SelectedSpawnLocation.Location.Z += 32.0f;
		SpawnActor(SelectRandomActor(),  SelectedSpawnLocation.Location);
	}
}

void UActorSpawnerComponent::SpawnWithStaticPosition()
{
	for (int32 i = 0; i < ActorsSpawnCount; i++)
	{
		SpawnActor(SelectRandomActor(), RootLocation);
	}
}

void UActorSpawnerComponent::SpawnActor(const int32 Index, const FVector& Location)
{
	// TODO spawn may fail -> suspecting collision with other actors
	auto SpawnedEnemy = GetWorld()->SpawnActor<AEnemyBase>(ActorsSpawnPool[Index].Get(), Location, FRotator(0.0f));
	if (not IsValid(SpawnedEnemy))
	{
		UE_LOG(LogTemp, Error, TEXT("Spawned enemy is not valid"));
		// throw std::exception();
	}
	else
	{
		SpawnedEnemy->OnDeathEvent.AddDynamic(ExperienceSystem, &AExperienceSystem::AddExperience);

		SpawnedActors.Add(SpawnedEnemy);
	}
	
}

bool UActorSpawnerComponent::ShouldSpawnActors(const float DeltaTime)
{
	if (not bPeriodicSpawnEnabled)
	{
		return false;
	}

	TimeSinceLastSpawn += DeltaTime;
	if (TimeSinceLastSpawn >= SpawnIntervalInSeconds)
	{
		TimeSinceLastSpawn -= SpawnIntervalInSeconds;

		return true;
	}

	return false;
}

int32 UActorSpawnerComponent::SelectRandomActor() const
{
	return FMath::RandRange(0, ActorsSpawnPool.Num() - 1);
}

int32 UActorSpawnerComponent::GetNumberOfWavesSpawned() const
{
	return WavesSpawned;
}

int32 UActorSpawnerComponent::GetNumberOfWavesLeft() const
{
	return WavesToSpawn - WavesSpawned;
}

float UActorSpawnerComponent::GetTimeToNextSpawn() const
{
	return SpawnIntervalInSeconds - TimeSinceLastSpawn;
}
