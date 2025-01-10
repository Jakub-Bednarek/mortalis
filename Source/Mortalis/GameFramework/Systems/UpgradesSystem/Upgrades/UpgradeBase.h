#pragma once

#include "GameFramework/Types/UpgradeIndex.h"
#include "GameFramework/Helpers/IndexGenerator.h"
#include "UpgradeUIData.h"

template <typename T>
class UpgradeBaseBuilder;

// consider switching concrete classes from UCLASS to USTRUCT if delegates allow such operation
// allocation object on heap seems like a waste and most of them are gonna act only as functor
// or will contain class of concrete spell that should be instantiated in game, no need to keep it in pure data types for upgrades
template <typename T, typename U>
class UpgradeBase
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

    FUpgradeUIData GetUpgradeUIData()
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
    // not sure about template, maybe 4 separate functions would suit it better?
    template <typename T>
    static T::Builder Create()
    {
        constexpr int32 SKILL_INDEX_UPPER_RANGE = 256;
        static IndexGenerator<FUpgradeIndex, FUpgradeIndex{0}, FUpgradeIndex{SKILL_INDEX_UPPER_RANGE}> Generator {};

        auto* UpgradeInstance = NewObject<T>();
        return { Generator.Get() , UpgradeInstance };
    }
};

template <typename T>
class UpgradeBaseBuilder
{
public:
    UpgradeBaseBuilder(const FUpgradeIndex Index, T* Target)
        : Target(Target)
    {
        assert(Target);
        Target->Index = Index;
    }

    UpgradeBaseBuilder& WithName(FName Name) { Target->Name = MoveTemp(Name); }

    UpgradeBaseBuilder& WithDescription(FName Description) { Target->Description = MoveTemp(Description); }

    T* Build() { return Target; }
private:
    T* Target;
};