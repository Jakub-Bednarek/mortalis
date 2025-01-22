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
        Value += 1;
        return temp;
    }

    bool operator>(const FUpgradeIndex& Rhs) const
    {
        return Value > Rhs.Value;
    }

    bool operator<(const FUpgradeIndex& Rhs) const
    {
        return Value < Rhs.Value;
    }

    bool operator>=(const FUpgradeIndex& Rhs) const
    {
        return not (Value < Rhs.Value);
    }

    bool operator<=(const FUpgradeIndex& Rhs) const
    {
        return not (Value > Rhs.Value);
    }

    bool operator==(const FUpgradeIndex& Rhs) const
    {
        return Value == Rhs.Value;
    }

    uint32 Value;
};

FORCEINLINE uint32 GetTypeHash(const FUpgradeIndex& Value)
{
    return Value.Value;
}