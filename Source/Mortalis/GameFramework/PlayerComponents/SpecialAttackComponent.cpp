// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"
#include "GameManager.h"

#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

USpecialAttackComponent::USpecialAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpecialAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> GameManagerActors {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameManager::StaticClass(), GameManagerActors);

	if (GameManagerActors.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Expected exactly one GameManager actor, found: %d"), GameManagerActors.Num());
	}
	else
	{
		auto* GameManager = (AGameManager*)(GameManagerActors[0]);
		GameManager->OnLevelRestartEvent.AddUObject(this, &USpecialAttackComponent::OnRestart);
	}
}

void USpecialAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpecialAttackComponent::Execute(UPlayerStatisticsComponent* PlayerStatistics)
{
	if (not CanExecuteAttack(PlayerStatistics))
	{
		return;
	}

	ExecuteAttack(PlayerStatistics);
}

void USpecialAttackComponent::ExecuteAttack(UPlayerStatisticsComponent* PlayerStatistics) 
{
	const auto Direction = CalculateAttackDirection();
	// TODO: change hardcoded offset to var
	auto TargetLocation = GetOwner()->GetActorLocation() + (150.0f * Direction);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(SpecialProjectile, TargetLocation, FRotator(0.0f));

	if (IsValid(SpawnedProjectile))
	{
		SpawnedProjectile->SetBaseDamage(PlayerStatistics->GetBaseNormalAttackDamage());
		SpawnedProjectile->Fire(Direction);
	}

	PlayerStatistics->ChangeCurrentMana(-AttackManaCost);
}

bool USpecialAttackComponent::CanExecuteAttack(const UPlayerStatisticsComponent* PlayerStatistics) const
{
	return PlayerStatistics->GetCurrentMana() >= AttackManaCost;
}

FVector USpecialAttackComponent::CalculateAttackDirection() const
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	// Most likely inefficient
	auto* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	
	APawn* ControlledPawn = PlayerController->GetPawn();
	if (ControlledPawn != nullptr)
	{
		auto ResultDirection = (Hit.Location - ControlledPawn->GetActorLocation()).GetSafeNormal();
		return FVector { ResultDirection.X, ResultDirection.Y, 0.0f };
	}

	return {};
}

void USpecialAttackComponent::OnRestart()
{
	UE_LOG(LogTemp, Log, TEXT("[SpecialAttackComponent] Restarting..."));
}