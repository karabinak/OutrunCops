#include "Road.h"

// Engine
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/Roads/RoadSpawner.h"
#include "OutrunCops/Gamemodes/GameplayGamemode.h"
#include "OutrunCops/Pickups/Pickup.h"


ARoad::ARoad()
{
	PrimaryActorTick.bCanEverTick = false;

	Road = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Road"));
	SpawnerTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnerTrigger"));
	CameraTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraTrigger"));
	Props = CreateDefaultSubobject<USceneComponent>(TEXT("PROPS"));
	Assets = CreateDefaultSubobject<USceneComponent>(TEXT("ASSETS"));
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	PickupSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("PickupSpawnLocation"));

	SetRootComponent(Road);
	SpawnerTrigger->SetupAttachment(GetRootComponent());
	CameraTrigger->SetupAttachment(GetRootComponent());
	Props->SetupAttachment(GetRootComponent());
	Assets->SetupAttachment(GetRootComponent());
	SpawnLocation->SetupAttachment(GetRootComponent());
	PickupSpawnLocation->SetupAttachment(GetRootComponent());
}

void ARoad::BeginPlay()
{
	Super::BeginPlay();

	SpawnerTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoad::OnSpawnerTriggerBeginOverlap);
	CameraTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoad::OnCameraChangeOverlap);
	CameraTrigger->OnComponentEndOverlap.AddDynamic(this, &ARoad::ChangeCameraEndOverlap);

	SpawnHealthPickup();
}

void ARoad::OnSpawnerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SpawnerRef)
	{
		SpawnerTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		SpawnerRef->SpawnRoad();
		AGameplayGamemode* Gamemode = Cast<AGameplayGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		Gamemode->SetPoliceSpawnLocation(FTransform(SpawnLocation->GetComponentRotation(), SpawnLocation->GetComponentLocation(), FVector(1.f, 1.f, 1.f)));
		Gamemode->SpawnPoliceCar();
	}
}

void ARoad::OnCameraChangeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVehiclePawn* Pawn = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn == OtherActor)
	{
		if (!bTunnel)
		{
			CameraTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		}
		Pawn->ChangeCamera(CameraChangeValue, bTunnel);
	}
}

void ARoad::ChangeCameraEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AVehiclePawn* Pawn = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn == OtherActor)
	{
		Pawn->EndChangCamera(bTunnel);
	}
}

void ARoad::SpawnHealthPickup()
{
	if (ChanceToSpawnPickup <= 0.f) return;
	if (ChanceToSpawnPickup >= FMath::FRandRange(0.0f, 1.0f))
	{
		if (Pickup)
		{
			FActorSpawnParameters ActorSpawnParameters;
			GetWorld()->SpawnActor<APickup>(Pickup, PickupSpawnLocation->GetComponentLocation(), FRotator(0.f, 0.f, 0.f), ActorSpawnParameters);
		}

	}
}
