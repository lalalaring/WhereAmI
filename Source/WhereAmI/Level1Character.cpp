// Fill out your copyright notice in the Description page of Project Settings.

#include "WhereAmI.h"
#include "Level1Character.h"
#include <algorithm>
#include "Interactive.h"


// Sets default values
ALevel1Character::ALevel1Character()
	:AGameCharacter()
{

	AmbientDust = new ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/AmbientDust.AmbientDust'"));
	Radio = new ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/Levels/ingame/01/ARadio_BP"));
	Table = new ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/Levels/ingame/01/ATable_BP"));

	GetCharacterMovement()->JumpZVelocity = .0f;

	ParticleDustComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Dust particles"));
	ParticleDustComponent->SetRelativeLocation(FVector(1400.0f, 0.0f, 0.0f));
	ParticleDustComponent->Template = AmbientDust->Object;
	ParticleDustComponent->AttachTo(RootComponent);

}

// Called every frame
void ALevel1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = GetActorLocation();
	if (location.X > 4900 || location.X < -4900 || location.Y > 4900 || location.Y < -4900)
		this->SetActorLocation(FVector(0, 0, 0), false, new FHitResult(), ETeleportType::TeleportPhysics);

	distanceWalked += GetVelocity().Size()*DeltaTime;

	if (distanceWalked > 300)
		SpawnRadio();

}

// Spawn level 1 radio
void ALevel1Character::SpawnRadio()
{
	if (radioSpawned)
		return;
	radioSpawned = true;

	SetActorLocation(FVector(0, 0, 0), false, new FHitResult(), ETeleportType::TeleportPhysics);

	FVector location = GetActorLocation() + GetActorForwardVector() * 2000;	
	FRotator rotation(.0f, 90.f+GetActorRotation().Yaw, .0f);
	FTransform transform = FTransform(location);
	transform.SetRotation(rotation.Quaternion());

	GetWorld()->SpawnActor(Radio->Class, &transform);
	GetWorld()->SpawnActor(Table->Class, &transform);
	
}