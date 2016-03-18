// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class WHEREAMI_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

public:

	/** Disable player movements/controls */
	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = Movement)
	bool disableMovement = false;

	/** Max distance of raytrace */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	int32 raycastDistance = 150;

	// Result of raytrace
	FHitResult *raycastHit;

	// Sets default values for this character's properties
	AGameCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Get result of raytrace*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Utils)
	FHitResult getRaycastHit();

	// Move player to forward/back
	void MoveForward(float delta);

	// Move player to right/left
	void MoveRight(float delta);

	// Process horizontal input for camera
	void CameraX(float delta);

	// Process vertical input for camera
	void CameraY(float delta);

	//Use key
	void Use();

private:

	//Process raytrace
	void Raytrace();

};
