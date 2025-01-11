#pragma once

#include "GameFramework/Types/UpgradeIndex.h"
#include "GameFramework/Helpers/IndexGenerator.h"
#include "UpgradeUIData.h"

template <typename T>
class UpgradeBaseBuilder;

// can't switch child types to USTRUCT() if base class is not a USTRUCT which is not possible as UpgradeBase is a template type
// the only need for USTRUCT/UCLASS is to be able to push it as delegate param, creating another wrapper is like bullshit
// cause we would need to make one for each type of upgrade -> bad
template <typename T, typename U>
struct UpgradeBase
{
    friend class UpgradeBaseBuilder<U>;
public:
    using Builder = UpgradeBaseBuilder<U>;

    UpgradeBase() = default;
    virtual ~UpgradeBase() = default;

    virtual void Apply(T*) const = 0;

    virtual FName CreateDescription() const
    {
        return Description;
    }

    FUpgradeUIData GetUIData()
    {
        return {
            Index,
            Name,
            Description
        };
    }

protected:

private:
    FUpgradeIndex Index;
    FName         Name;
    FName         Description;
};

class UpgradeFactory
{
public:
    template <typename T>
    static T::Builder Create()
    {
        constexpr FUpgradeIndex SKILL_INDEX_LOWER_RANGE { 0 };
        constexpr FUpgradeIndex SKILL_INDEX_UPPER_RANGE { 256 };
        static IndexGenerator<FUpgradeIndex, SKILL_INDEX_LOWER_RANGE, SKILL_INDEX_UPPER_RANGE> Generator {};

        auto* UpgradeInstance = NewObject<T>();
        return { Generator.Next(), UpgradeInstance };
    }
};

template <typename T>
class UpgradeBaseBuilder
{
public:
    UpgradeBaseBuilder(FUpgradeIndex&& Index, T* Target)
        : Target(Target)
    {
        assert(Target);
        Target->Index = MoveTemp(Index);
    }

    UpgradeBaseBuilder& WithName(FName Name) { Target->Name = MoveTemp(Name); }

    UpgradeBaseBuilder& WithDescription(FName Description) { Target->Description = MoveTemp(Description); }

    T* Build() { return Target; }
private:
    T* Target;
};