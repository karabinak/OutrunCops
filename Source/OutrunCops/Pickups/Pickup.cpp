#include "Pickup.h"

// Engine
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;


	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupStaticMesh"));
	PickupMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = PickupMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());

}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
	
}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVehiclePawn* Pawn = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn == OtherActor)
	{
		Pawn->AddHealth(HealthAmount);
		Destroy();
	}
}

float APickup::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	AddActorLocalRotation(FRotator(0.f, 1.5f, 0.f));
	AddActorWorldOffset(FVector(0.f, 0.f, TransformedCos()));
}

