#include "BaseRoad.h"

#include "Components/BoxComponent.h"
#include "BaseSpawner.h"

ABaseRoad::ABaseRoad()
{
	PrimaryActorTick.bCanEverTick = false;

	Road = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Road"));
	SpawnerTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnerTrigger"));

	SetRootComponent(Road);
	SpawnerTrigger->SetupAttachment(GetRootComponent());

}

void ABaseRoad::BeginPlay()
{
	Super::BeginPlay();

	SpawnerTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseRoad::OnSpawnerTriggerBeginOverlap);
}

void ABaseRoad::OnSpawnerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SpawnerRef)
	{
		SpawnerTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		SpawnerRef->SpawnRoad();
	}
}