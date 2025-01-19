// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerComponents/NormalAttackComponent.h"
#include "Projectiles/BasicProjectile.h"
#include "GameManager.h"

#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UNormalAttackComponent::UNormalAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNormalAttackComponent::BeginPlay()
{
	Super::BeginPlay();
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
	// TODO: change hardcoded offset to var
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
	FHitResult Hit;
	bool bHitSuccessful = false;

	// Most likely inefficient
	auto* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (not PlayerController)
	{
		return {};
	}
	
	APawn* ControlledPawn = PlayerController->GetPawn();
	if (ControlledPawn != nullptr)
	{
		auto ResultDirection = (Hit.Location - ControlledPawn->GetActorLocation()).GetSafeNormal();
		return FVector { ResultDirection.X, ResultDirection.Y, 0.0f };
	}

	return {};
}