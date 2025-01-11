// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Types/UpgradeCategory.h"

#include "CoreMinimal.h"

/**
 * 
 */

template <typename T>
struct Chain
{
    template <typename T>
    void RegisterUpgrade(T* Upgrade) 
    {
        Upgrades.Push(Upgrade);
    };

    void SetCategory(EUpgradeCategory NewCategory)
    {
        Category = NewCategory;
    }

    bool IsExhausted() const
    {
        return bIsExhausted;
    }

    T* GetNext()
    {
        check(Upgrades.Num() > 0);

        // TODO: correct index for extraction;
        return Upgrades[0];
    }

private:
    TArray<T*> Upgrades;

    EUpgradeCategory Category;

    bool bIsExhausted = false;
};