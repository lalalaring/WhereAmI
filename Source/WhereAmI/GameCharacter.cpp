// Fill out your copyright notice in the Description page of Project Settings.

#include "WhereAmI.h"
#include "GameCharacter.h"
#include <algorithm>
#include "Interactive.h"


// Sets default values
AGameCharacter::AGameCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	raycastHit = new FHitResult(ForceInit);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First person camera"));
	CameraComponent->AttachTo(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, .00f, 55.0f));
	CameraComponent->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Raytrace();
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &AGameCharacter::MoveForward);
	InputComponent->BindAxis("Right", this, &AGameCharacter::MoveRight);
	InputComponent->BindAxis("Rot_X", this, &AGameCharacter::CameraX);
	InputComponent->BindAxis("Rot_Y", this, &AGameCharacter::CameraY);
	InputComponent->BindAction("Use", EInputEvent::IE_Pressed, this, &AGameCharacter::Use);

}

// Return current raycast result
FHitResult AGameCharacter::getRaycastHit()
{
	return *raycastHit;
}

// Move to front/back
void AGameCharacter::MoveForward(float delta)
{
	if (!disableMovement)
		AddMovementInput(this->GetActorForwardVector(), delta);
}

// Move to right/left
void AGameCharacter::MoveRight(float delta)
{
	if (!disableMovement)
		AddMovementInput(this->GetActorRightVector(), delta);
}

// Move camera horizontally
void AGameCharacter::CameraX(float delta)
{
	if (!disableMovement)
	{
		FRotator r = GetActorRotation();
		r.Yaw += delta;
		SetActorRotation(r);
	}
}

// Move camera vertically
void AGameCharacter::CameraY(float delta)
{
	if (!disableMovement)
	{
		FRotator r = CameraComponent->RelativeRotation;
		r.Pitch = std::min(std::max(r.Pitch + delta, -50.0f), 70.0f);
		CameraComponent->SetRelativeRotation(r);
	}
}

// Process raytrace
void AGameCharacter::Raytrace()
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

	if (result.GetActor() != raycastHit->GetActor())
	{
		if (raycastHit->bBlockingHit)
			if(raycastHit->GetActor()->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
				IInteractive::Execute_EndView(raycastHit->GetActor(), this);
		if (result.GetActor())
			if (result.GetActor()->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
				IInteractive::Execute_StartView(result.GetActor(), this);
	}
	*raycastHit = result;


}

// Use event
void AGameCharacter::Use()
{
	if (raycastHit->bBlockingHit) {
		if (raycastHit->GetActor()->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
		{
			IInteractive::Execute_Use(raycastHit->GetActor(), this);
		}
	}
}