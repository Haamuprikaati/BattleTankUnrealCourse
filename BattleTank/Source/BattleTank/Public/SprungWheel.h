// Copyright Konsta K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:
	void SetupConstraints();

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};