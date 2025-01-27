// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CollisionSource.generated.h"
/**
 *
 */

UENUM()
enum class CollisionSource : uint8
{
    Environment UMETA(DisplayName = "Environment"),
    Enemy UMETA(DisplayName = "Enemy")
};