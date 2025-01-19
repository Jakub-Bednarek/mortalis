// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerComponents/SkillComponent.h"
#include "GameManager.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> GameManagerActors {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameManager::StaticClass(), GameManagerActors);

	if (GameManagerActors.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Expected exactly one GameManager actor, found: %d"), GameManagerActors.Num());
	}
	else
	{
		auto* GameManager = (AGameManager*)(GameManagerActors[0]);
		GameManager->OnLevelRestartEvent.AddUObject(this, &USkillComponent::OnRestart);
	}
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillComponent::OnRestart()
{
	UE_LOG(LogTemp, Log, TEXT("[SkillComponent] Restarting..."));
}