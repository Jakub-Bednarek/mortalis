#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/SkillComponentUpgrade.h"

#include "FireballSkillUpgrade.generated.h"

UCLASS()
class UFireballSkillUpgrade : public USkillComponentUpgrade
{
    GENERATED_BODY()
    
    class FireballSkillUpgradeBuilder : public UpgradeBaseBuilder<UFireballSkillUpgrade>
    {
    public:
        FireballSkillUpgradeBuilder(UFireballSkillUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}
    };

public:

    virtual void Apply(USkillComponent* Target) const override
    {
    }

};