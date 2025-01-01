// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/FollowPlayerComponent.h"

#include "FollowPlayerComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFollowPlayerComponent::UFollowPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UFollowPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}


// Called every frame
void UFollowPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsFollowingEnabled and Target != nullptr)
	{
		UpdateLocation(DeltaTime);
	}
}


void UFollowPlayerComponent::SetFollowingEnabled(bool Enabled)
{
	bIsFollowingEnabled = Enabled;

	Target = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerPawn reference."));
	}
}

void UFollowPlayerComponent::SetVelocity(const float Value)
{
	if (Value <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Velocity must be greater than 0."));
		return;
	}

	Velocity = Value;
}

void UFollowPlayerComponent::UpdateLocation(const float DeltaTime)
{
	auto CurrentLocation = Owner->GetActorLocation();
	auto Direction = Target->GetActorLocation() - CurrentLocation;
	Direction.Normalize();

	const auto LocationOffset = CurrentLocation + (Velocity * DeltaTime * Direction);
	Owner->SetActorLocation(FVector(LocationOffset.X, LocationOffset.Y, CurrentLocation.Z));
}