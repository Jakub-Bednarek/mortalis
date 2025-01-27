#pragma once

#include "GameFramework/Types/UpgradeIndex.h"
#include "GameFramework/Types/UpgradeCategory.h"

#include "CoreMinimal.h"

#include "UpgradeUIData.generated.h"

USTRUCT()
struct FUpgradeUIData
{
    GENERATED_BODY()

    // TODO: Why copy assignment OP is deleted for FName and can't use ref
    FName Name;
    FName Description;
    FUpgradeIndex Index;
    EUpgradeCategory Category;

    // TODO: Image
};