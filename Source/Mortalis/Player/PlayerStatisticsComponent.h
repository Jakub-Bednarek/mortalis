// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UI/Game/PlayerStatisticsHUD.h"

#include "PlayerStatisticsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORTALIS_API UPlayerStatisticsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatisticsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPlayerStatisticsHUD> PlayerStatisticsHUDClass;

private:
	TObjectPtr<UPlayerStatisticsHUD> PlayerStatisticsHUD;
};
