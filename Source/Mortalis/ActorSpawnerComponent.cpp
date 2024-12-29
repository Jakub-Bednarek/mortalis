// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerComponent.h"
#include "CoreGlobals.h"
#include "HAL/Platform.h"

#include "Logging/StructuredLog.h"
#include "NavMesh/RecastNavMesh.h"
#include "NavigationSystem.h"

// Sets default values for this component's properties
UActorSpawnerComponent::UActorSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	RootLocation = GetOwner()->GetRootComponent()->GetComponentLocation();
}


// Called every frame
void UActorSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	while (ShouldSpawnActors(DeltaTime))
	{
		Spawn();
	}

	// ...
}


void UActorSpawnerComponent::AddActorToSpawnPool(TSubclassOf<class UObject> Actor)
{
	ActorsSpawnPool.Add(Actor);
}


void UActorSpawnerComponent::SetActorSpawnPool(TArray<TSubclassOf<class UObject>> Actors)
{
	if (Actors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting actors spawn pool to an empty array."));
	}

	ActorsSpawnPool = Actors;
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

		SpawnedActors.Add(GetWorld()->SpawnActor<AActor>(ActorsSpawnPool[SelectRandomActor()].Get(), SelectedSpawnLocation.Location, FRotator(0.0f)));
	}
}

void UActorSpawnerComponent::SpawnWithStaticPosition()
{
	for (int32 i = 0; i < ActorsSpawnCount; i++)
	{
		SpawnedActors.Add(GetWorld()->SpawnActor<AActor>(ActorsSpawnPool[SelectRandomActor()].Get(), RootLocation, FRotator(0.0f)));
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
