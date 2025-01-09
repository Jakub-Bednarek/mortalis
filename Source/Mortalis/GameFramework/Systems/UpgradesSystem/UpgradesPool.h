// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Upgrades/UpgradesChain.h"

#include "CoreMinimal.h"

/**
 * 
 */

template <typename T>
class MORTALIS_API UpgradesPool
{
public:
	UpgradesPool() {}
	~UpgradesPool() {}

private:
	TArray<Chain<T>> RegisteredChains;
};
