// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Level1Character.generated.h"

UCLASS()
class WHEREAMI_API ALevel1Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Walk particle */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleDustComponent;

public:
	// Sets default values for this character's properties
	ALevel1Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	// Move player to forward/back
	void MoveForward(float delta);
	// Move player to right/left
	void MoveRight(float delta);
	// Process horizontal input for camera
	void CameraX(float delta);
	// Process vertical input for camera
	void CameraY(float delta);

	
	
};
