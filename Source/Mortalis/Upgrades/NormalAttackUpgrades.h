
#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/NormalAttackComponentUpgrade.h"

#include "NormalAttackUpgrades.generated.h"

UCLASS()
class UNormalAttackDamageUpgrade : public UNormalAttackComponentUpgrade
{
    GENERATED_BODY()
    
    class NormalAttackDamageUpgradeBuilder : public UpgradeBaseBuilder<UNormalAttackDamageUpgrade, NormalAttackDamageUpgradeBuilder>
    {
    public:
        NormalAttackDamageUpgradeBuilder(UNormalAttackDamageUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        NormalAttackDamageUpgradeBuilder& WithDamageValue(float Value)
        {
            Target->DamageDelta = Value;
        }
    };

public:
    using Builder = NormalAttackDamageUpgradeBuilder;

    virtual void Apply(UNormalAttackComponent* Target) const override
    {

    }

private:
    float DamageDelta = 10.0f;
};