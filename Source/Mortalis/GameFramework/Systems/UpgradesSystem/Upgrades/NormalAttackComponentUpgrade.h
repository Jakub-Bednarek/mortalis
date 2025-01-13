// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradeBase.h"
#include "GameFramework/PlayerComponents/NormalAttackComponent.h"

#include "CoreMinimal.h"

#include "NormalAttackComponentUpgrade.generated.h"

/**
 * 
 */

UCLASS()
class UNormalAttackComponentUpgrade : public UObject, public UpgradeBase<UNormalAttackComponent, UNormalAttackComponentUpgrade>
{
    GENERATED_BODY()

public:
    using BaseType = UpgradeBase<UNormalAttackComponent, UNormalAttackComponentUpgrade>;

    UNormalAttackComponentUpgrade() = default;
    virtual ~UNormalAttackComponentUpgrade() = default;

    virtual void Apply(UNormalAttackComponent*) const override {}
};