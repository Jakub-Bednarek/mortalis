// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradeBase.h"
#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"

#include "CoreMinimal.h"

#include "StatisticsComponentUpgrade.generated.h"

/**
 * 
 */

UCLASS()
class UStatisticsComponentUpgrade : public UObject, public UpgradeBase<UPlayerStatisticsComponent>
{
    GENERATED_BODY()

public:
    UStatisticsComponentUpgrade() = default;
    virtual ~UStatisticsComponentUpgrade() = default;
    
    virtual void Apply(UPlayerStatisticsComponent*) override {}
};