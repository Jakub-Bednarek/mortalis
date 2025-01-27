// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NormalAttackComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MORTALIS_API UNormalAttackComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNormalAttackComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void Execute(const UPlayerStatisticsComponent *PlayerStatistics);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectiles")
    TSubclassOf<AActor> NormalProjectile{};

protected:
    virtual void BeginPlay() override;

private:
    void UpdateAttackCooldown(float DeltaTime);

    void ExecuteAttack(const UPlayerStatisticsComponent *PlayerStatistics);
    void StartCooldownTimer(const UPlayerStatisticsComponent *PlayerStatistics);

    FVector CalculateAttackDirection() const;

private:
    float NextAttackCooldown = 0.0f;
};
