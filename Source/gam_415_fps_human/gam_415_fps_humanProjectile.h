// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gam_415_fps_humanProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config=Game)
class Agam_415_fps_humanProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UStaticMeshComponent* ballMesh; // Mesh component for the projectile mesh.
	
	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UMaterial* baseMat; // Material component to be applied to the projectile mesh and decal.

	UPROPERTY() // Unreal Property
		FLinearColor randColor; // Color object that can be randomized.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UMaterialInterface* projMat; // Material interface that can be used to modify the color of the projectile.

	UPROPERTY() // Unreal Property
		UMaterialInstanceDynamic* dmiMat; // Material instance that can be used to give each projectile a unique color.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UNiagaraSystem* colorP; // Niagara Particle System object for assigning random color to particle effects.

public:
	Agam_415_fps_humanProjectile();


protected:

	virtual void BeginPlay(); // Separated like this so that color randomization can be done as the projectile is spawned.


public:
	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

