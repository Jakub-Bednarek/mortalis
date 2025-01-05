// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Systems/ExperienceSystem.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, int32, Experience);

UCLASS()
class MORTALIS_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ProcessDeath();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Experience;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnDeath OnDeathEvent;
protected:
	virtual void BeginPlay() override;

private:
	int32 GetExperience() const;
};
