#pragma once

#include "CoreMinimal.h"

#include "UpgradeIndex.generated.h"

USTRUCT()
struct FUpgradeIndex
{
    GENERATED_BODY()

    FUpgradeIndex operator++(int)
    {
        auto temp = *this;
        value += 1;
        return temp;
    }

    bool operator>(const FUpgradeIndex& Rhs)
    {
        return value > Rhs.value;
    }

    bool operator<(const FUpgradeIndex& Rhs)
    {
        return value < Rhs.value;
    }

    bool operator>=(const FUpgradeIndex& Rhs)
    {
        return not (value < Rhs.value);
    }

    bool operator<=(const FUpgradeIndex& Rhs)
    {
        return not (value > Rhs.value);
    }

    uint32 value;
};