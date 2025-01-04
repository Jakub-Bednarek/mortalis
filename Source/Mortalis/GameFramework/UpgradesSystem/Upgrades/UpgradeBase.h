// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/Statistics/PlayerStatisticsComponent.h"

#include "UpgradeBase.generated.h"

UCLASS(Abstract)
class MORTALIS_API AUpgradeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgradeBase();

	virtual void Apply(UPlayerStatisticsComponent&);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
