// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

template <typename T>
struct Chain
{
    // Add enable_if to check if U is base class of T
    template <typename U>
    void RegisterUpgrade() {};

private:
    TArray<T*> Upgrades;
};