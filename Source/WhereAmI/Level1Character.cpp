// Fill out your copyright notice in the Description page of Project Settings.

#include "WhereAmI.h"
#include "Level1Character.h"
#include <algorithm>


// Sets default values
ALevel1Character::ALevel1Character()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->JumpZVelocity = .0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First person camera"));
	CameraComponent->AttachTo(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, .00f, 55.0f));
	CameraComponent->bUsePawnControlRotation = false;

	ParticleDustComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Dust particles"));
	ParticleDustComponent->SetRelativeLocation(FVector(1400.0f, 0.0f, 0.0f));
	ConstructorHelpers::FObjectFinder<UParticleSystem> AmbientDust(TEXT("ParticleSystem'/Game/Particles/AmbientDust.AmbientDust'"));
	ParticleDustComponent->Template = AmbientDust.Object;
	ParticleDustComponent->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ALevel1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevel1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = GetActorLocation();
	if (location.X > 4900 || location.X < -4900 || location.Y > 4900 || location.Y < -4900)
		this->SetActorLocation(FVector(0, 0, 0), false, new FHitResult(), ETeleportType::TeleportPhysics);
	

}

// Called to bind functionality to input
void ALevel1Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("Forward", this, &ALevel1Character::MoveForward);
	InputComponent->BindAxis("Right", this, &ALevel1Character::MoveRight);
	InputComponent->BindAxis("Rot_X", this, &ALevel1Character::CameraX);
	InputComponent->BindAxis("Rot_Y", this, &ALevel1Character::CameraY);

}

void ALevel1Character::MoveForward(float delta)
{
	AddMovementInput(this->GetActorForwardVector(), delta);
}

void ALevel1Character::MoveRight(float delta)
{
	AddMovementInput(this->GetActorRightVector(), delta);
}

void ALevel1Character::CameraX(float delta)
{
	FRotator r = GetActorRotation();
	r.Yaw += delta;
	SetActorRotation(r);
}

void ALevel1Character::CameraY(float delta)
{
	FRotator r = CameraComponent->RelativeRotation;
	r.Pitch =  std::min(std::max(r.Pitch + delta, -50.0f), 70.0f);
	CameraComponent->SetRelativeRotation(r);
}

