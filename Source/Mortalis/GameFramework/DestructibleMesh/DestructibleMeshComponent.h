// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "DestructibleMeshComponent.generated.h"

/**
 *
 */
struct FVertexDataBoundaries
{
    void AddVertexPosition(const FVector3f &Position)
    {
        if (not bIsInitialized)
        {
            XMax = Position.X;
            XMin = Position.X;

            YMax = Position.Y;
            YMin = Position.Y;

            ZMax = Position.Z;
            ZMin = Position.Z;

            bIsInitialized = true;

            return;
        }

        AddXPosition(Position.X);
        AddYPosition(Position.Y);
        AddZPosition(Position.Z);
    }

private:
    void AddXPosition(const float Position)
    {
        if (Position > XMax)
        {
            XMax = Position;
        }
        else if (Position < XMin)
        {
            XMin = Position;
        }
    }

    void AddYPosition(const float Position)
    {
        if (Position > YMax)
        {
            YMax = Position;
        }
        else if (Position < YMin)
        {
            YMin = Position;
        }
    }

    void AddZPosition(const float Position)
    {
        if (Position > ZMax)
        {
            ZMax = Position;
        }
        else if (Position < ZMin)
        {
            ZMin = Position;
        }
    }

public:
    bool bIsInitialized = false;

    float XMax;
    float XMin;

    float YMax;
    float YMin;

    float ZMax;
    float ZMin;
};

UCLASS()
class MORTALIS_API UDestructibleMeshComponent : public UStaticMeshComponent
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable)
    void SetCubeSize(float Size);

    UFUNCTION(BlueprintCallable)
    void CalculateCubePositions();

private:
    float CubeSize = 0.0f;

    TArray<FVector> TargetCubePositions{};
};
