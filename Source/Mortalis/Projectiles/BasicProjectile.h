// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicProjectile.generated.h"

UCLASS()
class MORTALIS_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectile();

public:
	void SetVelocity(float Value);
	void SetDurationInSeconds(float Value);
	void Fire(const FVector& Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void UpdatePosition(float DeltaTime);

	void OnProjectileHit();
	void OnProjectileExpire();

	void CalculateCurrentDuration(float DeltaTime);
	bool bIsExpired() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Velocity = 1300.0f;
	float DurationInSeconds = 2.0f;
	float CurrentDuration = 0.0f;

	bool bFired = false;

	FVector Direction = {};
};
