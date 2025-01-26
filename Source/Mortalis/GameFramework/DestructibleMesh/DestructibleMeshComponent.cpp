// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/DestructibleMesh/DestructibleMeshComponent.h"

#include "RawMesh.h"

void UDestructibleMeshComponent::SetCubeSize(const float Size)
{
    if (Size <= 0.0f)
    {
        UE_LOG(LogTemp, Error, TEXT("Cube size must be greater than 0.0, got: %f"), Size);   
    }
    CubeSize = Size;
}

void UDestructibleMeshComponent::CalculateCubePositions()
{
    UE_LOG(LogTemp, Log, TEXT("Calculating"));

    auto StaticMeshPtr = GetStaticMesh();
    if (StaticMeshPtr == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to retrieve static mesh"));
        return;
    }

    float MaxX = 0.0f;
    float MaxY = 0.0f;
    float MaxZ = 0.0f;
    FPositionVertexBuffer* VertexBuffer = &StaticMeshPtr->GetRenderData()->LODResources[0].VertexBuffers.PositionVertexBuffer;
    for (uint32 i = 0; i < VertexBuffer->GetNumVertices(); ++i)
    {
        auto VertexPosition = VertexBuffer->VertexPosition(i);
        UE_LOG(LogTemp, Log, TEXT("%s"), *(VertexPosition.ToString()));
    }
}