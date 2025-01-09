// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ExperienceSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterLevelUp, uint32, Level);

UCLASS(BlueprintType)
class MORTALIS_API AExperienceSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	AExperienceSystem();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddExperience(int32 Experience);

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnCharacterLevelUp OnCharacterLevelUp;

private:
	bool CanLevelUp() const;

	void LevelUp();

private:
	// this part could make use of some strategy pattern
	int32 CurrentLevel = 0;

	int32 CurrentExperience = 0;
	int32 ExperienceForNextLevel = 100;
};
