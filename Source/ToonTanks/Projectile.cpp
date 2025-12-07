// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	MoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Move Component"));
	MoveComponent->MaxSpeed = 1600.f;
	MoveComponent->InitialSpeed = 1600.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString HitCompName = HitComp->GetName();
	FString OtherActorName = OtherActor->GetName();
	FString OtherCompName = OtherComp->GetName();

	UE_LOG(LogTemp, Warning, TEXT("%s"), * HitCompName);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActorName);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherCompName);
}

