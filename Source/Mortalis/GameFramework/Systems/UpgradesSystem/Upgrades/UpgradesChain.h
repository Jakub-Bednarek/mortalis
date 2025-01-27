// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Types/UpgradeCategory.h"
#include "GameFramework/Types/ChainIndex.h"
#include "GameFramework/Types/UpgradeIndex.h"

#include "CoreMinimal.h"

/**
 *
 */
template <typename T> struct Chain
{
    Chain(FChainIndex Index) : Index(Index), NextUpgradeIndex(StartingUpgradeIndex), bIsExhausted(false) {}

    void RegisterUpgrade(T Upgrade) { Upgrades.Push(Upgrade); };

    void MarkNextUpgradeAsSelected()
    {
        check(NextUpgradeIndex < Upgrades.Num());

        ++NextUpgradeIndex;
        if (NextUpgradeIndex == Upgrades.Num())
        {
            bIsExhausted = true;
        }
    }

    bool IsExhausted() const { return bIsExhausted; }

    T &GetNextCandidate()
    {
        check(Upgrades.Num() > 0);
        check(NextUpgradeIndex != Upgrades.Num());
        check(not bIsExhausted);

        return Upgrades[NextUpgradeIndex];
    }

    TArray<FUpgradeIndex> GetAllUpgradesIndexes() const
    {
        TArray<FUpgradeIndex> Indexes{};
        for (const auto &Upgrade : Upgrades)
        {
            Indexes.Push(Upgrade->GetIndex());
        }

        return Indexes;
    }

    FChainIndex GetIndex() const { return Index; }

private:
    static constexpr TArray<T *>::SizeType StartingUpgradeIndex{0};

    // TODO: check if stability of elements guaranteed?
    FChainIndex Index;
    TArray<T> Upgrades{};
    TArray<T>::SizeType NextUpgradeIndex;
    bool bIsExhausted;
};