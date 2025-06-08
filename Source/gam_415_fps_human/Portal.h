// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"

class gam_415_fps_humanCharacter;

UCLASS()
class GAM_415_FPS_HUMAN_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		UStaticMeshComponent* mesh; // Static mesh component. Allows for a mesh to be applied to the actor.

	UPROPERTY(EditAnywhere, BlueprintReadWrite) // Blueprint editable and read/writable Unreal Property.
		USceneCaptureComponent2D* sceneCapture; // Scene capture component. Allows for a scene to be captured as an image and saved as a texture.

	UPROPERTY(EditAnywhere, BlueprintReadWrite) // Blueprint editable and read/writable Unreal Property.
		UTextureRenderTarget2D* renderTarget; // Texture render target. Allows for a scene capture image to be rendered to a mesh as a texture.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		UBoxComponent* boxComp; // Box component. Allows for the creation of an invisible hitbox.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		APortal* OtherPortal; // Portal class object. Allows for an eyedropper selection of another object of the same class to bind the two objects.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		UMaterialInterface* mat; // Material interface. Allows for a material to be applied to the actor.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property.
		UArrowComponent* rootArrow; // Arrow component. Creates an editor-only visible arrow for the actor. This will be used to determine where the player appears when teleported.

	UFUNCTION() // Unreal Function.
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		// Void function. Called when the player overlaps the box collision component.

	UFUNCTION() // Unreal Function.
		void SetBool(Agam_415_fps_humanCharacter* playerChar); // Void function. Allows for the boolean "isTeleporting" in the player character's header file to be modified.

	UFUNCTION() // Unreal Function.
		void UpdatePortals(); // Void function. Used to update the current scene capture being rendered to the portals.


};
