// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProc.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProc::APerlinProc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh"); // Creates the default object "Procedural Mesh" to have attachments added.
	ProcMesh->SetupAttachment(GetRootComponent()); // Assign the root component.
	
}

// Called when the game starts or when spawned
void APerlinProc::BeginPlay()
{
	Super::BeginPlay();

	CreateVertices(); // Creates Vertices for procedural mesh.
	CreateTriangles(); // Creates Triangles that make up the procedural mesh.
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true); // Creates the mesh in the world.
	ProcMesh->SetMaterial(0, Mat); // Applies material to mesh, even if it is deformed later.
	
}

// Called every frame
void APerlinProc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProc::AlterMesh(FVector impactPoint) // Morphs landscape when terrain is shot.
{

	for (int i = 0; i < Vertices.Num(); i++) // FOR loop used to determine the number of vertices at target location.
	{

		FVector tempVector = impactPoint - this->GetActorLocation(); // Find where the projectile landed.

		if (FVector(Vertices[i] - tempVector).Size() < radius) // Check for area to be updated.
		{

			Vertices[i] = Vertices[i] - Depth; // Used to get the new terrain depth.
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>()); // Update the terrain mesh, keeping it the same color and model but changing its shape.

		}

	}

}

void APerlinProc::CreateVertices()
{


	for (int X = 0; X <= XSize; X++) // FOR loop for determining the X size of the terrain mesh.
	{
		for (int Y = 0; Y <= YSize; Y++) // FOR loop for determining the Y size of the terrain mesh.
		{

			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier; // Use Perlin Noise to determine the dimensions of the terrain mesh, given the values plugged in.
			
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z)); // Debug message. Will not show up outside of the editor.
			
			Vertices.Add(FVector(X * Scale, Y * Scale, Z)); // Add the scale to Vertices.
			UV0.Add(FVector2D(X * UVScale, Y * UVScale)); // Add the UVscale to UV0.

		}



	}

}

void APerlinProc::CreateTriangles()
{
	int Vertex = 0; // Integer "Vertex" for determining dimensions.

	for (int X = 0; X < XSize; X++) // FOR loop for determining the X size of the vertices.
	{

		for (int Y = 0; Y < YSize; Y++) // FOR loop for determining the Y size of the vertices.
		{

			// How the vertices will be generated.
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			Vertex++; // Increment Vertex

		}

		Vertex++; // Increment Vertex

	}


}