#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/StatisticsComponentUpgrade.h"

#include "HealthUpgrade.generated.h"

UCLASS()
class UHealthUpgrade : public UStatisticsComponentUpgrade
{
    GENERATED_BODY()
    
    class HealthUpgradeBuilder : public UpgradeBaseBuilder<UHealthUpgrade>
    {
    public:
        HealthUpgradeBuilder(UHealthUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        HealthUpgradeBuilder& WithHealthValue(float Value) { Target->HealthDelta = Value; }
    };

public:
    using Builder = HealthUpgradeBuilder;

    virtual void Apply(UPlayerStatisticsComponent* Target) const override
    {
        Target->ChangeMaxHealth(HealthDelta);
    }

private:
    float HealthDelta = 10.0f;
};