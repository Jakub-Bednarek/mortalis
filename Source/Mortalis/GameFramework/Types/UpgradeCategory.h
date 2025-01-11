#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EUpgradeCategory : uint8
{
	Statistics UMETA(DisplayName="Statistics"),
	NormalAttack UMETA(DisplayName="Normal Attack"),
	SpecialAttack UMETA(DisplayName="Special Attack"),
	Skill UMETA(DisplayName="Skill"),
};
