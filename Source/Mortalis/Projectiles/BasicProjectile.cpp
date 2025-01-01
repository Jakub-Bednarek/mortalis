// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (not bFired)
	{
		return;
	}
	
	UpdatePosition(DeltaTime);
	CalculateCurrentDuration(DeltaTime);

	if (bIsExpired())
	{
		OnProjectileExpire();
	}
}

void ABasicProjectile::SetVelocity(float Value)
{
	if (Value < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Velocity of a projectile must be greater than 0."));
		return;
	}

	Velocity = Value;
}

void ABasicProjectile::SetDurationInSeconds(float Value)
{
	if (Value < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Duration of a projectile must be greater than 0."));
		return;
	}

	DurationInSeconds = Value;
}

void ABasicProjectile::Fire(const FVector& TargetDirection)
{
	Direction = TargetDirection;
	Direction.Normalize();

	bFired = true;
}

void ABasicProjectile::OnProjectileHit()
{

}

void ABasicProjectile::OnProjectileExpire()
{
	Destroy();
}

void ABasicProjectile::UpdatePosition(float DeltaTime)
{
	auto ProjectilePositionOffset = GetActorLocation() + (DeltaTime * Velocity * Direction);

	SetActorLocation(ProjectilePositionOffset);
}

void ABasicProjectile::CalculateCurrentDuration(const float DeltaTime)
{
	CurrentDuration += DeltaTime;
}

bool ABasicProjectile::bIsExpired() const
{
	return CurrentDuration >= DurationInSeconds;
}
