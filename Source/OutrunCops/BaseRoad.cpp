#include "BaseRoad.h"

#include "Components/BoxComponent.h"
#include "BaseVehiclePawn.h"
#include "Kismet/GameplayStatics.h"
#include "BaseSpawner.h"
#include "OutrunCopsGameModeGameplay.h"

ABaseRoad::ABaseRoad()
{
	PrimaryActorTick.bCanEverTick = false;

	Road = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Road"));
	SpawnerTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnerTrigger"));
	CameraTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraTrigger"));

	SetRootComponent(Road);
	SpawnerTrigger->SetupAttachment(GetRootComponent());
	CameraTrigger->SetupAttachment(GetRootComponent());

}

void ABaseRoad::BeginPlay()
{
	Super::BeginPlay();

	SpawnerTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseRoad::OnSpawnerTriggerBeginOverlap);
	CameraTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseRoad::OnCameraChangeOverlap);
}

void ABaseRoad::OnSpawnerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SpawnerRef)
	{
		SpawnerTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		SpawnerRef->SpawnRoad();
		AOutrunCopsGameModeGameplay* Gamemode = Cast<AOutrunCopsGameModeGameplay>(UGameplayStatics::GetGameMode(GetWorld()));
		Gamemode->SpawnPoliceCar();
	}
}

void ABaseRoad::OnCameraChangeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseVehiclePawn* Pawn = Cast<ABaseVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn == OtherActor)
	{
		Pawn->ChangeCamera(CameraChangeValue);
	}
}
