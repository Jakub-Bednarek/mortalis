// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpecialAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORTALIS_API USpecialAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpecialAttackComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Execute(const UPlayerStatisticsComponent* PlayerStatistics);

protected:
	virtual void BeginPlay() override;		
};
