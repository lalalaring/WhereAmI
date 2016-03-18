// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"
#include "Level1Character.generated.h"

UCLASS()
class WHEREAMI_API ALevel1Character : public AGameCharacter
{
	GENERATED_BODY()

	/** Walk particle */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleDustComponent;

	ConstructorHelpers::FObjectFinder<UParticleSystem> *AmbientDust;

	ConstructorHelpers::FClassFinder<AActor> *Table;
	ConstructorHelpers::FClassFinder<AActor> *Radio;

public:

	/** Distance that player walked */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	int32 distanceWalked = 0;

	// Sets default values for this character's properties
	ALevel1Character();
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	// Spawn radio
	bool radioSpawned = false;
	void SpawnRadio();
	
};
