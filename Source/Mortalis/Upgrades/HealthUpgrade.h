#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/StatisticsComponentUpgrade.h"

#include "HealthUpgrade.generated.h"

UCLASS()
class UHealthUpgrade : public UStatisticsComponentUpgrade
{
    GENERATED_BODY()

    virtual void Apply(UPlayerStatisticsComponent* Target) const override
    {
        Target->ChangeMaxHealth(10);
    }
};