#pragma once

#include "CoreMinimal.h"

#include "ChainIndex.generated.h"

USTRUCT()
struct FChainIndex
{
    GENERATED_BODY()

    FChainIndex operator++(int)
    {
        auto temp = *this;
        Value += 1;
        return temp;
    }


    bool operator>(const FChainIndex& Rhs) const
    {
        return Value > Rhs.Value;
    }

    bool operator<(const FChainIndex& Rhs) const
    {
        return Value < Rhs.Value;
    }

    bool operator>=(const FChainIndex& Rhs) const
    {
        return not (Value < Rhs.Value);
    }

    bool operator<=(const FChainIndex& Rhs) const
    {
        return not (Value > Rhs.Value);
    }

    bool operator==(const FChainIndex& Rhs) const
    {
        return Value == Rhs.Value;
    }

    uint32 Value;
};

FORCEINLINE uint32 GetTypeHash(const FChainIndex& Value)
{
    return Value.Value;
}