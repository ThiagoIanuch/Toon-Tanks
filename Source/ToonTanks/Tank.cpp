// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h" 
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	if (TankPlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;

		TankPlayerController->GetHitResultUnderCursor(
			ECC_Visibility, 
			false, 
			HitResult);

		DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			25.f,
			12,
			FColor::Red,
			false,
			-1);

		RotateTurret(HitResult.ImpactPoint, DeltaTime);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::Turn);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}

void ATank::Move(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaLocation = FVector::ZeroVector;

	DeltaLocation.X = Value * Speed * DeltaTime;

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation = FRotator::ZeroRotator;

	DeltaRotation.Yaw = Value * TurnRate * DeltaTime;;

	AddActorLocalRotation(DeltaRotation, true);
}
