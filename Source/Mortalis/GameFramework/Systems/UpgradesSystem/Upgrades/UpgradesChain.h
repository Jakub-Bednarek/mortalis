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

    bool IsExhausted() const
    {
        return bIsExhausted;
    }

    T* GetNextCandidate()
    {
        check(Upgrades.Num() > 0);
        check(not bIsExhausted);

        // TODO: correct index for extraction;
        return Upgrades[0];
    }

private:
    // TODO: check if stability of elements guaranteed?
    TArray<T*> Upgrades;

    bool bIsExhausted = false;
};