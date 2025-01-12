// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Types/UpgradeCategory.h"
#include "GameFramework/Types/ChainIndex.h"

#include "CoreMinimal.h"

/**
 * 
 */
template <typename T>
struct Chain
{
    Chain(FChainIndex Index) : Index(Index), bIsExhausted(false), NextUpgradeIndex(StartingUpgradeIndex) {}

    template <typename T>
    void RegisterUpgrade(T* Upgrade) 
    {
        Upgrades.Push(Upgrade);
    };

    void MarkNextUpgradeAsSelected()
    {
        check(NextUpgradeIndex < Upgrades.Num());

        ++NextUpgradeIndex;
    }

    bool IsExhausted() const
    {
        return bIsExhausted;
    }

    T* GetNextCandidate()
    {
        check(Upgrades.Num() > 0);
        check(NextUpgradeIndex != Upgrades.Num());
        check(not bIsExhausted);

        return Upgrades[NextUpgradeIndex];
    }

    TArray<typename T::IndexType> GetAllUpgradesIndexes() const
    {
        TArray<typename T::IndexType> Indexes {};
        for (const auto& Upgrade : Upgrades)
        {
            Indexes.Push(Upgrade->GetIndex());
        }

        return Indexes;
    }

    FChainIndex GetIndex() const
    {
        return Index;
    }

private:
    // TODO: check if stability of elements guaranteed?
    static constexpr TArray<T*>::SizeType StartingUpgradeIndex { 0 };
 
    TArray<T*>           Upgrades {};
    TArray<T*>::SizeType NextUpgradeIndex;
    FChainIndex          Index;
    bool                 bIsExhausted;
};