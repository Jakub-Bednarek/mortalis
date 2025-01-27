#pragma once

#include <type_traits>
#include <cassert>

#include "CoreMinimal.h"

/*
    Generates sequence of indexes in range <Min, Max> both inclusive
*/
template <typename T, T Min, T Max> class IndexGenerator
{
public:
    T Next()
    {
        if (NextVal > Max)
        {
            assert(false && "Index generator exhausted given range");
            return Max;
        }

        return NextVal++;
    }

private:
    T NextVal = Min;
};