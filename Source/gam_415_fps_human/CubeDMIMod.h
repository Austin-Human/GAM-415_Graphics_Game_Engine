// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIMod.generated.h"

class UNiagaraSystem;


UCLASS()
class GAM_415_FPS_HUMAN_API ACubeDMIMod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeDMIMod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UBoxComponent* boxComp; // Sets up hit box component.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UStaticMeshComponent* cubeMesh; // Creates cube mesh.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UMaterialInterface* baseMat; // Base material for cube.

	UPROPERTY() // Unreal Property
		UMaterialInstanceDynamic* dmiMat; // Dynamic Material Instance for randomizing and changing cube material.

	UPROPERTY(EditAnywhere) // Blueprint editable Unreal Property
		UNiagaraSystem* colorP; // Niagara Particle System object for assigning random color to particle effects.

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);





};
