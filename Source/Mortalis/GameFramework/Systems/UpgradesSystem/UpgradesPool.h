// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Types/PoolIndex.h"
#include "GameFramework/Types/UpgradeIndex.h"
#include "GameFramework/Helpers/IndexGenerator.h"

#include "Upgrades/UpgradesChain.h"
#include "Upgrades/UpgradeUIData.h"

#include "CoreMinimal.h"
#include <cstddef>

/**
 * 
 */

// this is wrong, pools should contain all the data and proxies should manage indexes returned by the pool
// this way it will be easier and cheaper to add/remove/mark as X specific skills/chains

template <typename T>
class UpgradesPoolFactory;

template <typename T>
class MORTALIS_API UpgradesPool
{
	friend class UpgradesPoolFactory<T>;

public:
	UpgradesPool(): bIsExhausted(true) {}
	~UpgradesPool() {}

	void RegisterChain(Chain<T>&& Value)
	{
		if (RegisteredChains.Contains(Value.GetIndex()))
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrades chain with index: %d is already registered."), Value.GetIndex().Value);
			return;
		}

		if (not Value.IsExhausted())
		{
			bIsExhausted = false;
		}

		AddMappingForAllChainUpgrades(Value.GetIndex(), Value.GetAllUpgradesIndexes());
		ActiveChains.Add(Value.GetIndex());
		RegisteredChains.Emplace(Value.GetIndex(), MoveTemp(Value));

		UE_LOG(LogTemp, Log, TEXT("Successfuly registered new chain with index: %d"), Value.GetIndex().Value);
	}

	bool IsExhausted() const
	{
		return bIsExhausted;
	}

	FUpgradeUIData GetUIDataFromRandomlySelected()
	{
		check(not bIsExhausted);

		const auto RandomElementIndex = FMath::RandRange(0, (ActiveChains.Num() - 2));
		if (not ActiveChains.IsValidIndex(RandomElementIndex))
		{
			UE_LOG(LogTemp, Error, TEXT("Generated Index is not a valid index for active chain."));
			return {};
		}

		auto* SelectedChain = RegisteredChains.Find(ActiveChains[RandomElementIndex]);
		if (SelectedChain == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Selected active ChainIndex is not a valid index for registered chain."));
			return {};
		}

		return SelectedChain->GetNextCandidate()->GetUIData();
	}

	Chain<T> CreateChain()
	{
		auto Index = ChainIndexGenerator.Next();
		
        UE_LOG(LogTemp, Error, TEXT("New index generated: %d"), Index.Value);
		return Chain<T> { Index };
	}

	T SelecteNextUpgrade(const FUpgradeIndex UpgradeIndex)
	{
		const auto* ChainIndex = UpgradeToChainMapping.Find(UpgradeIndex);
		if (ChainIndex == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Lookup failed, no ChainIndex associated with given UpgradeIndex: %d."), UpgradeIndex.Value);
			return nullptr;
		}

		auto ChainInstance = RegisteredChains.Find(*ChainIndex);
		if (ChainInstance == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Lookup failed, no Chain associated with given ChainIndex: %d."), ChainIndex->Value);
			return nullptr;
		}

		T UpgradeApplier = ChainInstance->GetNextCandidate();

		ChainInstance->MarkNextUpgradeAsSelected();
		if (ChainInstance->IsExhausted())
		{
			ActiveChains.Remove(*ChainIndex);
			ExhaustedChains.Add(*ChainIndex);

			if (ActiveChains.Num() == 0)
			{
				bIsExhausted = true;
			}
		}

		return UpgradeApplier;
	}

private:
	void AddMappingForAllChainUpgrades(const FChainIndex ChainIndex, const TArray<FUpgradeIndex>& UpgradeIndexes)
	{
		for (const auto UpgradeIndex : UpgradeIndexes)
		{
			UpgradeToChainMapping.Emplace(UpgradeIndex, ChainIndex);
		}
	}

private:
	static constexpr FChainIndex MIN_CHAIN_INDEX { 0 };
	static constexpr FChainIndex MAX_CHAIN_INDEX { 128 };
	IndexGenerator<FChainIndex, MIN_CHAIN_INDEX, MAX_CHAIN_INDEX> ChainIndexGenerator {};

	// BLEH, need to find a better way, that's gonna hurt cache imo and looks ugly af
	TMap<FUpgradeIndex, FChainIndex> UpgradeToChainMapping {};
	TMap<FChainIndex, Chain<T>> 	 RegisteredChains {};
	TArray<FChainIndex> 			 ActiveChains {};
	TSet<FChainIndex> 				 ExhaustedChains {};
	bool							 bIsExhausted;
};