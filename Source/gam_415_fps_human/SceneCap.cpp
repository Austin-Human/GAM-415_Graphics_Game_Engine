// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneCap.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default value
ASceneCap::ASceneCap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent")); // Create the Scene Capture Component object in the editor.
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh"); // Create the Static Mesh object in the editor.

	RootComponent = cubeMesh; // Make the Static Mesh object the Root Component.
	SceneCaptureComponent->SetupAttachment(cubeMesh); // Attach the Scene Capture Component object to the Root Component (Cube Mesh).
	
	RenderTarget = NewObject<UTextureRenderTarget2D>(); // Create the Render Target object to allow for the real-time scene capture to be rendered onto an object.

	SceneCaptureComponent->TextureTarget = RenderTarget; // Render the scene capture texture to the desired target.

}

// Called when the game starts or when spawned
void ASceneCap::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASceneCap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

