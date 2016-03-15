// Fill out your copyright notice in the Description page of Project Settings.

#include "WhereAmI.h"
#include "Level1Character.h"
#include <algorithm>
#include "IInteractive.h"


// Sets default values
ALevel1Character::ALevel1Character()
{

	raycastDistance = 1000;

	AmbientDust = new ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/AmbientDust.AmbientDust'"));
	Radio = new ConstructorHelpers::FClassFinder<ARadio>(TEXT("/Game/Levels/ingame/01/ARadio_BP"));


	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	raycastHit = new FHitResult(ForceInit);

	GetCharacterMovement()->JumpZVelocity = .0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First person camera"));
	CameraComponent->AttachTo(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, .00f, 55.0f));
	CameraComponent->bUsePawnControlRotation = false;

	ParticleDustComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Dust particles"));
	ParticleDustComponent->SetRelativeLocation(FVector(1400.0f, 0.0f, 0.0f));
	ParticleDustComponent->Template = AmbientDust->Object;
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

	distanceWalked += GetVelocity().Size()*DeltaTime;

	if (distanceWalked > 300)
		SpawnRadio();
	
	Raytrace();

	/*if (raycastHit && raycastHit->GetComponent())
		raycastHit->GetComponent()->bRenderCustomDepth = true;*/

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

FHitResult ALevel1Character::getRaycastHit()
{
	return *raycastHit;
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
	
}

void ALevel1Character::Raytrace()
{

	FTransform cameraTransform = CameraComponent->GetComponentTransform();
	FVector start = cameraTransform.GetLocation();
	FRotator rotation = cameraTransform.Rotator();
	FVector end = start + rotation.Vector() * raycastDistance;

	FCollisionQueryParams traceParams(FName(TEXT("PlayerTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.bTraceAsyncScene = true;
	traceParams.bReturnPhysicalMaterial = true;

	FHitResult result(ForceInit);

	GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, traceParams);
	if (result.bBlockingHit)
		hittingActor = result.Actor.Get();
	else
		hittingActor = NULL;

	if (hittingActor != raycastHit->Actor.Get()) {
		IInteractive* usable = Cast<IInteractive>(raycastHit->Actor.Get());
		if (usable)
			usable->EndView.Broadcast();
		IInteractive* newUsable = Cast<IInteractive>(hittingActor);
		if (newUsable)
			newUsable->StartView.Broadcast();
	}

	raycastHit = &result;


}

void ALevel1Character::Use()
{
	if (hittingActor) {
		IInteractive* usable = Cast<IInteractive>(hittingActor);
		if (usable)
			usable->Use.Broadcast();
	}
}