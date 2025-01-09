#pragma once

template <typename T>
class UpgradeBase
{
public:
    UpgradeBase() = default;
    virtual ~UpgradeBase() = default;

    virtual void Apply(T*) = 0;
};