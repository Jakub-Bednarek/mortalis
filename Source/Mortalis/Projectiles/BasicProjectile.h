// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/Types/CollisionSource.h"

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
	void SetBaseDamage(float Value);

	UFUNCTION(BlueprintCallable)
	void OnProjectileHit();
	
	UFUNCTION(BlueprintCallable)
	float GetDamage() const;

	UFUNCTION(BlueprintCallable)
	bool GetHasCollided() const;

	UFUNCTION(BlueprintCallable)
	void OnCollisionEnter(const CollisionSource Source);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void UpdatePosition(float DeltaTime);

	void OnProjectileExpire();

	void CalculateCurrentDuration(float DeltaTime);
	bool bIsExpired() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Velocity = 1300.0f;
	float DurationInSeconds = 2.0f;
	float CurrentDuration = 0.0f;
	float BaseDamage = 0.0f;

	bool bFired = false;
	bool bHasCollided = false;

	FVector Direction = {};
};
