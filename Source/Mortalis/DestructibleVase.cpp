// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleVase.h"
#include "GameFramework/DestructibleMesh/DestructibleMeshComponent.h"

// Sets default values
ADestructibleVase::ADestructibleVase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DestructibleMesh = CreateDefaultSubobject<UDestructibleMeshComponent>(TEXT("Destructible Static Mesh"));
}

// Called when the game starts or when spawned
void ADestructibleVase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleVase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

