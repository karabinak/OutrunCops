#include "Enemy.h"

// Engine
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"

// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/Gamemodes/GameplayGamemode.h"

//////////////////////////////////////////////////////

AEnemy::AEnemy()
{
	ArrestedZone = CreateDefaultSubobject<USphereComponent>("ArrestedZone");
	ArrestedZone->SetupAttachment(GetMesh());

	// CAR PARTS
	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_Wheel"));
	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_Wheel"));
	WheelRL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RL_Wheel"));
	WheelRR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RR_Wheel"));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	Siren = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumper"));
	Mirrors = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mirrors"));

	WheelFL->SetupAttachment(GetMesh(), TEXT("FL"));
	WheelFR->SetupAttachment(GetMesh(), TEXT("FR"));
	WheelRL->SetupAttachment(GetMesh(), TEXT("RL"));
	WheelRR->SetupAttachment(GetMesh(), TEXT("RR"));

	FrontBumper->SetupAttachment(GetMesh());
	Siren->SetupAttachment(GetMesh());
	Mirrors->SetupAttachment(GetMesh());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	ArrestedZone->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OverlappingWithPlayer);
	ArrestedZone->OnComponentEndOverlap.AddDynamic(this, &AEnemy::StopOverlappingWithPlayer);

	PlayerPawn = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	Gamemode = Cast<AGameplayGamemode>(UGameplayStatics::GetGameMode(this));

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddImpulse(GetActorForwardVector() * SpawnForce);

}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DistanceFromPlayer();
	AIMovement();
}

void AEnemy::AIMovement()
{
	if (PlayerPawn)
	{
		FRotator DirectionRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
		FRotator DeltaNormalized = UKismetMathLibrary::NormalizedDeltaRotator(DirectionRotation, GetActorRotation());
		double Steering = UKismetMathLibrary::MapRangeClamped(DeltaNormalized.Yaw, -20.f, 20.f, -1.f, 1.f);

		if (DeltaNormalized.Yaw > -90.f && DeltaNormalized.Yaw < 90.f)
		{
			GetVehicleMovement()->SetThrottleInput(0.95f);
			GetVehicleMovement()->SetBrakeInput(0.f);
			GetVehicleMovement()->SetSteeringInput(Steering);
		}
		else
		{
			GetVehicleMovement()->SetThrottleInput(0.f);
			GetVehicleMovement()->SetBrakeInput(1.f);
			GetVehicleMovement()->SetSteeringInput(-Steering);
		}
	}
}

void AEnemy::DistanceFromPlayer()
{
	float PlayerDistance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	if (PlayerDistance >= DestroyDistance)
	{
		if (Gamemode)
		{
			Gamemode->SetPoliceAmount(-1);
			Destroy();
		}
	}
}

void AEnemy::OverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerPawn == OtherActor)
	{
		Gamemode->SetAmountOfChasersInSphere(1);
	}
}

void AEnemy::StopOverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerPawn == OtherActor)
	{
		Gamemode->SetAmountOfChasersInSphere(-1);
	}
}