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
class USkillComponentUpgrade : public UObject, public UpgradeBase<USkillComponent>
{
    GENERATED_BODY()

public:
    USkillComponentUpgrade() = default;
    virtual ~USkillComponentUpgrade() = default;

    virtual void Apply(USkillComponent*) override {}
};