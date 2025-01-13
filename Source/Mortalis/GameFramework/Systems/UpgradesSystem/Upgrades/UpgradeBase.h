#pragma once

#include "GameFramework/Types/UpgradeIndex.h"
#include "GameFramework/Types/UpgradeCategory.h"
#include "GameFramework/Helpers/IndexGenerator.h"
#include "UpgradeUIData.h"

#include "CoreMinimal.h"

template <typename T>
class UpgradeBaseBuilder;

UENUM()
enum class UpgradeState : uint8
{
    Idle,
    SelectionCandidate,
    Selected
};

// can't switch child types to USTRUCT() if base class is not a USTRUCT which is not possible as UpgradeBase is a template type
// the only need for USTRUCT/UCLASS is to be able to push it as delegate param, creating another wrapper is like bullshit
// cause we would need to make one for each type of upgrade -> bad
template <typename T, typename U>
struct UpgradeBase
{
public:
    using IndexType = FUpgradeIndex;

    UpgradeBase() = default;
    virtual ~UpgradeBase() = default;

    virtual void Apply(T*) const = 0;

    virtual FName CreateDescription() const
    {
        return Description;
    }

    IndexType GetIndex() const
    {
        return Index;
    }

    FUpgradeUIData GetUIData() const
    {
        return {
            Name,
            Description,
            Index,
            Category
        };
    }

    void SetName(FName&& Value)
    {
        Name = MoveTemp(Value);
    }

    void SetDescription(FName&& Value)
    {
        Description = Value;
    }

    // TODO: find a way to remove SetIndex and allow builder to set it, problematic part is allowing friend access from childs child pov
    // Or make it one time assignment only and print error otherwise -> you fucking moron pass it in the constructor
    void SetIndex(const FUpgradeIndex Value)
    {
        Index = Value;
    }

    void SetCategory(const EUpgradeCategory Value)
    {
        Category = Value;
    }

private:
    FName            Name;
    FName            Description;
    FUpgradeIndex    Index;
    EUpgradeCategory Category;
};

class UpgradeFactory
{
public:
    template <typename T>
    static T::Builder Create()
    {
        constexpr FUpgradeIndex SKILL_INDEX_LOWER_RANGE { 0 };
        constexpr FUpgradeIndex SKILL_INDEX_UPPER_RANGE { 1024 };
        static IndexGenerator<FUpgradeIndex, SKILL_INDEX_LOWER_RANGE, SKILL_INDEX_UPPER_RANGE> Generator {};

        auto* UpgradeInstance = NewObject<T>();
        return { UpgradeInstance, Generator.Next() };
    }
};

template <typename T>
class UpgradeBaseBuilder
{
public:
    UpgradeBaseBuilder(T* Target, FUpgradeIndex&& Index)
        : Target(Target)
    {
        assert(Target);
        Target->SetIndex(MoveTemp(Index));
    }

    UpgradeBaseBuilder& WithName(FName Name) { Target->SetName(MoveTemp(Name)); return *this; }

    UpgradeBaseBuilder& WithDescription(FName Description) { Target->SetDescription(MoveTemp(Description)); return *this; }

    UpgradeBaseBuilder& WithCategory(EUpgradeCategory Category) { Target->SetCategory(Category); return *this; }

    T* Build() { return Target; }

protected:
    T* Target;
};