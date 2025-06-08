// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "gam_415_fps_humanCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create subobjects for each component.
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	// Establish "boxComp" as the root component.
	RootComponent = boxComp;

	// Setup attachments for actor.
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	// Disable collision for the mesh.
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);


}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	// Setup a "begin overlap" trigger.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	
	// Make the root mesh hidden to the scene capture. This prevents it from blocking the capture's view.
	mesh->SetHiddenInSceneCapture(true);

	if (mat) // Check if applied material is valid.
	{
		
		mesh->SetMaterial(0, mat); // Apply material to mesh.

	}


}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePortals(); // Updates portals every tick. This makes the render like a video feed for the portals.

}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Agam_415_fps_humanCharacter* playerChar = Cast<Agam_415_fps_humanCharacter>(OtherActor); // Cast to the player character.

	if (playerChar) // Check if player character is valid.
	{
		if (OtherPortal) // Check for other linked portal.
		{
			if (!playerChar->isTeleporting) // Check if player is "teleporting" already.
			{
				
				playerChar->isTeleporting = true; // Set player's "teleporting" status to true.
				FVector loc = OtherPortal->rootArrow->GetComponentLocation(); // Get the location of the arrow component. This is where the player will appear at.
				playerChar->SetActorLocation(loc); // Teleport the player to the other side.

				// Set up a timer after the player emerges from the portal so they are not instantly teleported again.
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);


			}

		}

	}


}


void APortal::SetBool(Agam_415_fps_humanCharacter* playerChar)
{
	if (playerChar) // Checks if player is valid.
	{

		playerChar->isTeleporting = false; // Set player's teleporting status to "false".

	}


}

void APortal::UpdatePortals()
{

	// Called every tick. Updates the current scene being rendered to the portals.
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector CombinedLocation = camLocation + Location;

	// Apply updated scene to the portals.
	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);

}