#include "BaseEnemy.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "BaseVehiclePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "OutrunCopsGameModeGameplay.h"

ABaseEnemy::ABaseEnemy()
{
	ArrestedZone = CreateDefaultSubobject<USphereComponent>("ArrestedZone");
	ArrestedZone->SetupAttachment(GetMesh());
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	ArrestedZone->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OverlappingWithPlayer);
	ArrestedZone->OnComponentEndOverlap.AddDynamic(this, &ABaseEnemy::StopOverlappingWithPlayer);

	BaseVehicle = Cast<ABaseVehiclePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	Gamemode = Cast<AOutrunCopsGameModeGameplay>(UGameplayStatics::GetGameMode(this));

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddImpulse(GetActorForwardVector() * SpawnForce);

}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float PlayerDistance = (BaseVehicle->GetActorLocation() - GetActorLocation()).Size();
	if (PlayerDistance >= DespawnDistance)
	{
		if (Gamemode)
		{
			Gamemode->SetPoliceAmount(-1);
			Destroy();
		}
	}

	if (BaseVehicle)
	{
		FRotator DirectionRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), BaseVehicle->GetActorLocation());
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

void ABaseEnemy::OverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (BaseVehicle == OtherActor)
	{
		Gamemode->SetAmountOfChasersInSphere(1);
	}
}

void ABaseEnemy::StopOverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (BaseVehicle == OtherActor)
	{
		Gamemode->SetAmountOfChasersInSphere(-1);
	}
}