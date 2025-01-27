// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStatisticsComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MORTALIS_API UEnemyStatisticsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEnemyStatisticsComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.0f;
};
