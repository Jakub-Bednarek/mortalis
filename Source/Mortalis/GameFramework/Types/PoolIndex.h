#pragma once

#include "CoreMinimal.h"

#include "PoolIndex.generated.h"

USTRUCT()
struct FPoolIndex
{
    GENERATED_BODY()

    FPoolIndex operator++(int)
    {
        auto temp = *this;
        Value += 1;
        return temp;
    }

    bool operator>(const FPoolIndex &Rhs) const { return Value > Rhs.Value; }

    bool operator<(const FPoolIndex &Rhs) const { return Value < Rhs.Value; }

    bool operator>=(const FPoolIndex &Rhs) const { return not(Value < Rhs.Value); }

    bool operator<=(const FPoolIndex &Rhs) const { return not(Value > Rhs.Value); }

    bool operator==(const FPoolIndex &Rhs) const { return Value == Rhs.Value; }

    uint32 Value;
};

FORCEINLINE uint32 GetTypeHash(const FPoolIndex &Value) { return Value.Value; }