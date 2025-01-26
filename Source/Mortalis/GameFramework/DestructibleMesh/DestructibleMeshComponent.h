// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "DestructibleMeshComponent.generated.h"

/**
 * 
 */
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

	TArray<FVector> TargetCubePositions {};
};
