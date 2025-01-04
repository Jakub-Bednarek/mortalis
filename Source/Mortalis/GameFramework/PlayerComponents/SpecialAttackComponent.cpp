// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"

USpecialAttackComponent::USpecialAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpecialAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USpecialAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpecialAttackComponent::Execute(const UPlayerStatisticsComponent*)
{
	UE_LOG(LogTemp, Log, TEXT("Special attack bitch"));
}