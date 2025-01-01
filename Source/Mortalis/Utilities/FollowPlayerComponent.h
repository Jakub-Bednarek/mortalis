// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowPlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORTALIS_API UFollowPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFollowPlayerComponent();

	UFUNCTION(BlueprintCallable, category="Configuration")
	void SetFollowingEnabled(bool Enabled);

	UFUNCTION(BlueprintCallable, category="Configuration")
	void SetVelocity(float Value);

private:
	void UpdateLocation(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsFollowingEnabled = false;

	float Velocity = 200.0f;

	APawn* Target;
	AActor* Owner;
};
