#pragma once

#include "CoreMinimal.h"

#include "UpgradeRarity.generated.h"

UENUM()
enum class EUpgradeTier : uint8
{
    Normal UMETA(DisplayName = "Normal"),
    Magic UMETA(DisplayName = "Magic"),
    Rare UMETA(DisplayName = "Rare"),
    Extrodinary UMETA(DisplayName = "Extrodinary")
};