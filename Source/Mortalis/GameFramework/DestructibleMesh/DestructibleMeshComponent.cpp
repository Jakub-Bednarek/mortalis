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

    FVertexDataBoundaries MeshVertexBoundaries {};
    FPositionVertexBuffer* VertexBuffer = &StaticMeshPtr->GetRenderData()->LODResources[0].VertexBuffers.PositionVertexBuffer;
    for (uint32 i = 0; i < VertexBuffer->GetNumVertices(); ++i)
    {
        auto VertexPosition = VertexBuffer->VertexPosition(i);
        MeshVertexBoundaries.AddVertexPosition(VertexPosition);
        UE_LOG(LogTemp, Log, TEXT("%s"), *(VertexPosition.ToString()));
    }

    UE_LOG(LogTemp, Log, TEXT("[X] Max: %f | Min: %f [X] Max: %f | Min: %f [Z] Max: %f | Min: %f"), MeshVertexBoundaries.XMax, MeshVertexBoundaries.XMin, MeshVertexBoundaries.YMax, MeshVertexBoundaries.YMin, MeshVertexBoundaries.ZMax, MeshVertexBoundaries.ZMin);

    TArray<FVector> NormalizedVertices {};
    FVector CurrentVertex {};
    for (uint32 i = 0; i < VertexBuffer->GetNumVertices(); i++)
    {
      auto& VertexPosition = VertexBuffer->VertexPosition(i);
      CurrentVertex.X = (VertexPosition.X - MeshVertexBoundaries.XMin) / (MeshVertexBoundaries.XMax - MeshVertexBoundaries.XMin);
      CurrentVertex.Y = (VertexPosition.Y - MeshVertexBoundaries.YMin) / (MeshVertexBoundaries.YMax - MeshVertexBoundaries.YMin);
      CurrentVertex.Z = (VertexPosition.Z - MeshVertexBoundaries.ZMin) / (MeshVertexBoundaries.ZMax - MeshVertexBoundaries.ZMin);

      NormalizedVertices.Add(CurrentVertex);
      UE_LOG(LogTemp, Log, TEXT("Normalized: %s"), *(CurrentVertex.ToString()));
    }

    // Mesh bounds calculation -> we want to know the size of a mesh to create proper number of slots for cubes
    UpdateBounds();

    FTransform MeshTransform {};
    auto MeshBounds = CalcBounds(MeshTransform).BoxExtent;

    UE_LOG(LogTemp, Log, TEXT("Bounds: %s"), *(MeshBounds.ToString()));
}
