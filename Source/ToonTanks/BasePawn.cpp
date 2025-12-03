// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::RotateTurret(FVector LookAtTarget, float DeltaTime)
{
	FVector	ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation, 
			DeltaTime, 
			5.f)
		);
}

void ABasePawn::Fire()
{
	UE_LOG(LogTemp, Display, TEXT("FIRE"));

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();


	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);

	//DrawDebugSphere(
	//	GetWorld(),
	//	ProjectileSpawnPointLocation,
	//	25.f,
	//	12,
	//	FColor::Red,
	//	false,
	//	3.f);
}