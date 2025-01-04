// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerComponents/NormalAttackComponent.h"
#include "Projectiles/BasicProjectile.h"

#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UNormalAttackComponent::UNormalAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNormalAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Extract to base class (and fetch value in separate system?)
	const auto ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ViewportCenter = FVector(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f, 0.0f);
}

// TODO: set tick periodicity to every 5 frames
void UNormalAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateAttackCooldown(DeltaTime);
}

void UNormalAttackComponent::Execute(const UPlayerStatisticsComponent* PlayerStatistics)
{
	if (not (NextAttackCooldown <= 0.0f))
	{
		return;
	}

	ExecuteAttack(PlayerStatistics);
	StartCooldownTimer(PlayerStatistics);
}

void UNormalAttackComponent::UpdateAttackCooldown(const float DeltaTime)
{
	if (NextAttackCooldown <= 0.0f)
	{
		return;
	}

	NextAttackCooldown -= DeltaTime;
}

void UNormalAttackComponent::ExecuteAttack(const UPlayerStatisticsComponent* PlayerStatistics)
{
	const auto Direction = CalculateAttackDirection();
	auto TargetLocation = GetOwner()->GetActorLocation() + (150.0f * Direction);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(NormalProjectile, TargetLocation, FRotator(0.0f));

	if (IsValid(SpawnedProjectile))
	{
		SpawnedProjectile->SetBaseDamage(PlayerStatistics->GetBaseNormalAttackDamage());
		SpawnedProjectile->Fire(Direction);
	}
}

void UNormalAttackComponent::StartCooldownTimer(const UPlayerStatisticsComponent* PlayerStatistics)
{
	NextAttackCooldown = 1.0f / PlayerStatistics->GetAttacksPerSecond();
}

// TODO: when mouse is in the corner projectiles have slight offset but when on Axis they're perfectly fine
FVector UNormalAttackComponent::CalculateAttackDirection() const
{
	float MouseX;
	float MouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY);

	auto Direction = (ViewportCenter - FVector(MouseX, MouseY, 0.0f));
	Direction.Normalize();
	Direction = FVector(Direction.Y, -Direction.X, 0.0f); // Swap X and Y coordinates to align with world axis

	if (Direction.X == 0.0f and Direction.Y == 0.0f)
	{
		return FVector(0.5f, 0.5f, 0.0f);
	}

	return Direction;
}