// Copyright Konsta K.


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);
	Mass->SetNotifyRigidBodyCollision(true);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Suspension = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Suspension"));
	Suspension->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
