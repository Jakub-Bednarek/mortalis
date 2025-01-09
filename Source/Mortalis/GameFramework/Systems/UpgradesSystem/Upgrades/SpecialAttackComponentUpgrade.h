// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradeBase.h"
#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"

#include "CoreMinimal.h"

#include "SpecialAttackComponentUpgrade.generated.h"

/**
 * 
 */

UCLASS()
class USpecialAttackComponentUpgrade : public UObject, public UpgradeBase<USpecialAttackComponent>
{
    GENERATED_BODY()

public:
    USpecialAttackComponentUpgrade() = default;
    virtual ~USpecialAttackComponentUpgrade() = default;
    
    virtual void Apply(USpecialAttackComponent*) override {}
};