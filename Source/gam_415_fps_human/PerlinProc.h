// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProc.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class GAM_415_FPS_HUMAN_API APerlinProc : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProc();

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0)) // Blueprint editable Unreal Property. Clamps at 0.
		int XSize = 0; // Integer for X size.

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0)) // Blueprint editable Unreal Property. Clamps at 0.
		int YSize = 0; // Integer for Y size.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0)) // Blueprint editable Unreal Property with blueprint read/write functionality. Clamps at 0.
		float ZMultiplier = 1.0f; // Float for Z scale.

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0)) // Blueprint editable Unreal Property. Clamps at 0.
		float NoiseScale = 1.0f; // Float used for noise scale. Determines how rough the terrain will be.

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001)) // Blueprint editable Unreal Property. Clamps at 0.000001.
		float Scale = 0; // Float used for scale. Determines overall size of terrain.

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001)) // Blueprint editable Unreal Property. Clamps at 0.000001.
		float UVScale = 0; // Float used for UV scale. Used for materials.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		float radius; // Float used for radius.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		FVector Depth; // Depth vector. Used to determine how deep the terrain mesh will go.


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		UMaterialInterface* Mat; // Material interface used for the terrain mesh to assign a material.

private:

	UProceduralMeshComponent* ProcMesh; // Procedural mesh component to generate mesh based on inputs.

	// Arrays to store values used for terrain generation, rendering, and alteration.
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0; // Integer used for storing section ID. Helps to update terrain.

	void CreateVertices(); // Function call to "CreateVerticles".
	void CreateTriangles(); // Function call to "CreateTriangles".



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() // Unreal Function.
		void AlterMesh(FVector impactPoint); // Function call to "AlterMesh". Used to alter the terrain mesh when projectile impacts it.

};
