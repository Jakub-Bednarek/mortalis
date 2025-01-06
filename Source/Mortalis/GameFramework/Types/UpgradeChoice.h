// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UpgradeChoice.generated.h"
/**
 * 
 */

UENUM()
enum class UpgradeChoice : uint8
{
	First UMETA(DisplayName="First"),
	Second UMETA(DisplayName="Second"),
	Third UMETA(DisplayName="Third")
};