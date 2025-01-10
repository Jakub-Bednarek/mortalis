// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

private:
    TArray<T*> Upgrades;
};