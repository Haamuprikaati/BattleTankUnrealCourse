// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming states
UENUM()
enum class EFiringState : uint8
{
	Reloading, 
	Aiming,
	Locked
};

//Forward declaration
class UTankBarrel;
class UTankTurret;

//Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Set turret reference
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector OutHitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
		
	void MoveBarrelTowards(FVector AimDirection);

	UTankTurret* Turret = nullptr;

	void MoveTurretTowards(FVector AimDirection);

};
