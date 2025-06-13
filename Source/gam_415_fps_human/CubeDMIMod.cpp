// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "gam_415_fps_humanCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Subobjects.
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	// Make the box collision component the root component.
	RootComponent = boxComp;

	// Attach the cube mesh, the mesh to be applied to the actor, to the box collision component.
	cubeMesh->SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin); // Trigger for when box collision is overlapped by another actor (usually the player).

	if (baseMat) // Check is material is valid.
	{

		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this); // Apply chosen material to the cube.

	}

	if (cubeMesh) // Check if the mesh is valid.
	{

		cubeMesh->SetMaterial(0, dmiMat); // Set the material of the mesh.

	}

}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	Agam_415_fps_humanCharacter* overlappedActor = Cast<Agam_415_fps_humanCharacter>(OtherActor); // Cast to the player character. This is used to see if the player has overlapped with the box collision component.

	if (overlappedActor) // Check if the player overlapped with the box collision.
	{

		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f); // Get a random float.
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f); // Get a random float.
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f); // Get a random float.

		FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.f); // Using the three random floats, create a new color.
		
		if (dmiMat) // Check if the dynamic material instance is valid.
		{
			
			dmiMat->SetVectorParameterValue("Color", randColor); // Set the color to the newly created random color.
			dmiMat->SetScalarParameterValue("Darkness", ranNumX); // Set the shade of the new color. Allows for different colors as well as shading (Ex. can have light blue, blue, dark blue, or anything in between).
			
			if (colorP) // Checks for particle color.
			{
				// Randomize particle effect and color.
				UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);

				particleComp->SetNiagaraVariableLinearColor(FString("RandColor"), randColor); // Sets the particle color equal to the cube's color.

			}

		}

	}

}

