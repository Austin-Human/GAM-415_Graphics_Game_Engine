// Copyright Epic Games, Inc. All Rights Reserved.

#include "gam_415_fps_humanPickUpComponent.h"

Ugam_415_fps_humanPickUpComponent::Ugam_415_fps_humanPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void Ugam_415_fps_humanPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &Ugam_415_fps_humanPickUpComponent::OnSphereBeginOverlap);
}

void Ugam_415_fps_humanPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	Agam_415_fps_humanCharacter* Character = Cast<Agam_415_fps_humanCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
