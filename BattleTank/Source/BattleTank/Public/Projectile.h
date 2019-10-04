// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		URadialForceComponent* ExplosionForce = nullptr;

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ProjectileDamage = 20;

	void OnTimerExpired();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float DestroyDelay = 10;

};
