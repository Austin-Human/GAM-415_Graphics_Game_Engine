// Copyright Epic Games, Inc. All Rights Reserved.

#include "gam_415_fps_humanProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

Agam_415_fps_humanProjectile::Agam_415_fps_humanProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &Agam_415_fps_humanProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh"); // Create a component subobject for "Ball Mesh", which will be used for the projectile.

	// Set as root component
	RootComponent = CollisionComp; // Create a root component for "CollisionComp", which will allow for the splat decal to be applied on hit.

	ballMesh->SetupAttachment(CollisionComp); // Setup the "CollisionComp" to the projectile ball mesh.

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void Agam_415_fps_humanProjectile::BeginPlay() // Called when the projectile is spawned.
{
	Super::BeginPlay();

	// Create a random color to be applied to the projectile and splat decal.
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);

	dmiMat = UMaterialInstanceDynamic::Create(projMat, this); // Create an instance of the dynamic material for each projectile spawned.
	ballMesh->SetMaterial(0, dmiMat); // Set the spawned projectile's material to the newly created dynamic material instance (will only be applied to the new projectile. Previous and newer projectiles will also be unique).

	dmiMat->SetVectorParameterValue("ProjColor", randColor); // Set the parameter "ProjColor" in blueprint to the random color so it displays the random color in game.


}

void Agam_415_fps_humanProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	if (OtherActor != nullptr) // Check if what the projectile hit is valid so it can spawn the splat decal.
	{

		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.f); // Get a random number to use for choosing 1 of 4 splat textures from the grid.

		// Create the splat texture with its color applied on hit.
		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		MatInstance->SetVectorParameterValue("Color", randColor);
		MatInstance->SetScalarParameterValue("Frame", frameNum);

	}



}