#pragma once

#include "CoreMinimal.h"

#include "ChainIndex.generated.h"

USTRUCT()
struct FChainIndex
{
    GENERATED_BODY()

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
        return Value == Value;
    }

    uint32 Value;
};

FORCEINLINE uint32 GetTypeHash(const FChainIndex& Value)
{
    return Value.Value;
}