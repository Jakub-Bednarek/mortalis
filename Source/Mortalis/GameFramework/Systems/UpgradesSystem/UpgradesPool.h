// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Upgrades/UpgradesChain.h"
#include "Upgrades/UpgradeUIData.h"

#include "CoreMinimal.h"

/**
 * 
 */

// this is wrong, pools should contain all the data and proxies should manage indexes returned by the pool
// this way it will be easier and cheaper to add/remove/mark as X specific skills/chains
template <typename T>
class MORTALIS_API UpgradesPool
{
public:
	UpgradesPool() {}
	~UpgradesPool() {}

	FUpgradeUIData GetUIDataFromRandomlySelected()
	{
		// TODO: return random
		return {};
	}

private:
	TArray<Chain<T>> RegisteredChains;
};
