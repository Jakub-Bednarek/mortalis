// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Systems/ExperienceSystem.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradesSystem.generated.h"

UCLASS()
class MORTALIS_API AUpgradesSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	AUpgradesSystem();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ProcessCharacterLevelUp(uint32 Level);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AExperienceSystem* ExperienceSystem;
};
