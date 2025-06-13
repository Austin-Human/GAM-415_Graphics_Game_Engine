// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMeshFromStatic::AProcMeshFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Establish subobjects.
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");

	// Make the procedural mesh the root component.
	RootComponent = procMesh;

	// Attach the base mesh, the mesh component to be applied to the actor, to the procedural mesh component.
	baseMesh->SetupAttachment(procMesh);

}

// Called when the game starts or when spawned
void AProcMeshFromStatic::BeginPlay()
{
	
	GetMeshData(); // Get the data of the applied mesh.
	
}

void AProcMeshFromStatic::PostActorCreated()
{

	GetMeshData(); // Get the data of the applied mesh.

}

void AProcMeshFromStatic::PostLoad()
{

	Super::PostLoad();
	GetMeshData(); // Get the data of the applied mesh.

}

void AProcMeshFromStatic::GetMeshData()
{

	UStaticMesh* mesh = baseMesh->GetStaticMesh(); // Get the applied static mesh that will be rendered.

	if (mesh) // Check if the mesh is valid.
	{

		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents); // Get each section of the static mesh to be rendered.

		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents); // Apply the values of the applied static mesh.
		CreateMesh(); // Create the static mesh object in the world.

	}


}

void AProcMeshFromStatic::CreateMesh()
{

	if (baseMesh) // Check if the base mesh object is valid.
	{

		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true); // Create each individual mesh section. This is how the mesh will be rendered.

	}

}


void AProcMeshFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

