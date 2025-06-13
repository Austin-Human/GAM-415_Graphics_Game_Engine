// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMeshFromStatic.generated.h"


class UProceduralMeshComponent;

UCLASS()
class GAM_415_FPS_HUMAN_API AProcMeshFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcMeshFromStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // Begin Play function. Called when actor is created/spawned.

	virtual void PostActorCreated() override; // Post Actor Created function. Called after the actor is created/spawned.

	virtual void PostLoad() override; // Post load function. Called after actor's data is loaded.

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		TArray<FVector> Vertices; // Array for storing vertices.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		TArray<int> Triangles; // Array for storing triangles.

	UPROPERTY() // Unreal Property.
		TArray<FVector> Normals; // Array for storing normals.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		TArray<FVector2D> UV0; // Array for storing texture UVs.

	UPROPERTY() // Unreal Property.
		TArray<FLinearColor> VertexColors; // Array to store the color of each vertex.

		TArray<FColor> UpVertexColors; // Array to store the color of each triangle.

		TArray<FProcMeshTangent> Tangents; // Array to store vertexes.
	
	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		UStaticMeshComponent* baseMesh; // Static mesh component. Allows for a static mesh to be applied to the actor.


private:
	UProceduralMeshComponent* procMesh; // Procedural mesh component. Allows for a mesh to be created without strictly needing the editor.
	
	void GetMeshData(); // Function to get the data of the chosen mesh.
	void CreateMesh(); // Create the mesh using the provided shape. Allows for rendering of a mesh without needing it applied to the actor in the editor.

};
