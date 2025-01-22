#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/StatisticsComponentUpgrade.h"

#include "StatisticsUpgrades.generated.h"

// Actually that's bullshit, StatisticsComponentUpgrade should provide base builder with all base statistics with() function,
// that would reduce the code by 70% as it's gonna be boilerplate and will remove one layer of inheritance for every class
// or we could create still create class for each type of upgrade, but autofill most of the data like name, description etc only requiring actuall value for a concrete upgrade
UCLASS()
class UStatisticsHealthUpgrade : public UStatisticsComponentUpgrade
{
    GENERATED_BODY()
    
    class HealthUpgradeBuilder : public UpgradeBaseBuilder<UStatisticsHealthUpgrade, HealthUpgradeBuilder>
    {
    public:
        HealthUpgradeBuilder(UStatisticsHealthUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        HealthUpgradeBuilder& WithHealthValue(float Value) { Target->HealthDelta = Value; return *this; }
    };

public:
    using Builder = HealthUpgradeBuilder;

    virtual void Apply(UPlayerStatisticsComponent* Target) const override
    {
        Target->ChangeMaxHealth(HealthDelta);
    }

private:
    float HealthDelta = 0.0f;
};

UCLASS()
class UStatisticsDamageUpgrade : public UStatisticsComponentUpgrade
{
    GENERATED_BODY()
    
    class DamageUpgradeBuilder : public UpgradeBaseBuilder<UStatisticsDamageUpgrade, DamageUpgradeBuilder>
    {
    public:
        DamageUpgradeBuilder(UStatisticsDamageUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        DamageUpgradeBuilder& WithDamageValue(float Value) { Target->DamageDelta = Value; return *this; }
    };

public:
    using Builder = DamageUpgradeBuilder;

    virtual void Apply(UPlayerStatisticsComponent* Target) const override
    {
        Target->IncreaseDamage(DamageDelta);
    }

private:
    float DamageDelta = 0.0f;
};

UCLASS()
class UStatisticsAttackSpeedUpgrade : public UStatisticsComponentUpgrade
{
    GENERATED_BODY()
    
    class AttackSpeedUpgradeBuilder : public UpgradeBaseBuilder<UStatisticsAttackSpeedUpgrade, AttackSpeedUpgradeBuilder>
    {
    public:
        AttackSpeedUpgradeBuilder(UStatisticsAttackSpeedUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        AttackSpeedUpgradeBuilder& WithAttackSpeedValue(float Value) { Target->AttackSpeedDelta = Value; return *this; }
    };

public:
    using Builder = AttackSpeedUpgradeBuilder;

    virtual void Apply(UPlayerStatisticsComponent* Target) const override
    {
        Target->IncreaseAttackSpeed(AttackSpeedDelta);
    }

private:
    float AttackSpeedDelta = 0.0f;
};

UCLASS()
class UStatisticsMovementSpeedUpgrade : public UStatisticsComponentUpgrade
{
    GENERATED_BODY()
    
    class MovementSpeedUpgradeBuilder : public UpgradeBaseBuilder<UStatisticsMovementSpeedUpgrade, MovementSpeedUpgradeBuilder>
    {
    public:
        MovementSpeedUpgradeBuilder(UStatisticsMovementSpeedUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        MovementSpeedUpgradeBuilder& WithMovementSpeedValue(float Value) { Target->MovementSpeedDelta = Value; return *this; }
    };

public:
    using Builder = MovementSpeedUpgradeBuilder;

    virtual void Apply(UPlayerStatisticsComponent* Target) const override
    {
        Target->IncreaseMovementSpeed(MovementSpeedDelta);
    }

private:
    float MovementSpeedDelta = 0.0f;
};

UCLASS()
class UStatisticsRegenerationUpgrade : public UStatisticsComponentUpgrade
{
    GENERATED_BODY()
    
    class RegenerationUpgradeBuilder : public UpgradeBaseBuilder<UStatisticsRegenerationUpgrade, RegenerationUpgradeBuilder>
    {
    public:
        RegenerationUpgradeBuilder(UStatisticsRegenerationUpgrade* Target, FUpgradeIndex&& Index) : UpgradeBaseBuilder(Target, MoveTemp(Index)) {}

        RegenerationUpgradeBuilder& WithHealthRegenerationValue(float Value) { Target->HealthRegenerationDelta = Value; return *this; }
        RegenerationUpgradeBuilder& WithManaRegenerationValue(float Value) { Target->ManaRegenerationDelta = Value; return *this; }
    };

public:
    using Builder = RegenerationUpgradeBuilder;

    virtual void Apply(UPlayerStatisticsComponent* Target) const override
    {
        Target->IncreaseHealthRegeneration(HealthRegenerationDelta);
        Target->IncreaseManaRegeneration(ManaRegenerationDelta);
    }

private:
    float HealthRegenerationDelta = 0.0f;
    float ManaRegenerationDelta = 0.0f;
};