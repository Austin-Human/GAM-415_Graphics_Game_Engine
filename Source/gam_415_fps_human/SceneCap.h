// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include <GameplayStatics.generated.h>
#include "SceneCap.generated.h"



UCLASS()
class GAM_415_FPS_HUMAN_API ASceneCap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneCap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components) // Blueprint editable and writable Unreal Property.
		USceneCaptureComponent2D* SceneCaptureComponent; // Scene Capture Component. Allows for a scene in-game to be captured by an invisible camera (not quite a camera component, but similar).

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UStaticMeshComponent* cubeMesh; // Creates cube mesh.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UTextureRenderTarget2D* RenderTarget; // Render Target 2D. Allows for real-time scene capture to be rendered in-game.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
