// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradeBase.h"
#include "GameFramework/PlayerComponents/SkillComponent.h"

#include "CoreMinimal.h"

#include "SkillComponentUpgrade.generated.h"

/**
 * 
 */

UCLASS()
class USkillComponentUpgrade : public UObject, public UpgradeBase<USkillComponent, USkillComponentUpgrade>
{
    GENERATED_BODY()

public:
    using BaseType = UpgradeBase<USkillComponent, USkillComponentUpgrade>;

    USkillComponentUpgrade() = default;
    virtual ~USkillComponentUpgrade() = default;

    virtual void Apply(USkillComponent*) const override {}
};