#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/SkillComponentUpgrade.h"

#include "SkillUpgrades.generated.h"

UCLASS()
class UFireballSkillUpgrade : public USkillComponentUpgrade
{
    GENERATED_BODY()
    
    class FireballSkillUpgradeBuilder : public UpgradeBaseBuilder<UFireballSkillUpgrade, FireballSkillUpgradeBuilder>
    {
    public:
        FireballSkillUpgradeBuilder(UFireballSkillUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}
    };

public:

    virtual void Apply(USkillComponent* Target) const override
    {
    }

};