// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTimeInSeconds);
	if (bIsReloaded)
	{
		//Spawn a projectile at the socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		//UE_LOG(LogTemp, Warning, TEXT("%s firing"), *this->GetName());

	}
}