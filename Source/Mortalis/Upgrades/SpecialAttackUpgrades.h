
#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/SpecialAttackComponentUpgrade.h"

#include "SpecialAttackUpgrades.generated.h"

UCLASS()
class USpecialAttackDamageUpgrade : public USpecialAttackComponentUpgrade
{
    GENERATED_BODY()
    
    class SpecialAttackDamageUpgradeBuilder : public UpgradeBaseBuilder<USpecialAttackDamageUpgrade, SpecialAttackDamageUpgradeBuilder>
    {
    public:
        SpecialAttackDamageUpgradeBuilder(USpecialAttackDamageUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        SpecialAttackDamageUpgradeBuilder& WithDamageValue(float Value)
        {
            Target->DamageDelta = Value;
        }
    };

public:
    using Builder = SpecialAttackDamageUpgradeBuilder;

    virtual void Apply(USpecialAttackComponent* Target) const override
    {

    }

private:
    float DamageDelta = 10.0f;
};