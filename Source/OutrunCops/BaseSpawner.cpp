#include "BaseSpawner.h"

#include "BaseRoad.h"

ABaseSpawner::ABaseSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnRoad();
	SpawnRoad();
}

void ABaseSpawner::SpawnRoad()
{
	// Random Road Generator
	const int32 RandNumber = FMath::RandRange(0, RoadCollection.Num() - 1);
	UClass* SelectedRoad = RoadCollection[RandNumber];

	// Getting Vector And Rotator to spawn new road
	if (!SpawnedRoads.IsEmpty())
	{
		FTransform SocketTransform = SpawnedRoads[SpawnedRoads.Num() - 1]->GetMesh()->GetSocketTransform("AttachSocket");
		SpawnLocation = SocketTransform.GetLocation();
		SpawnRotation = SocketTransform.GetRotation().Rotator();
	}

	// Destroying Last Road
	if (SpawnedRoads.Num() >= MaxSpawnedRoads)
	{
		SpawnedRoads[0]->Destroy();
		SpawnedRoads.RemoveAt(0);
	}

	// Create Road
	FActorSpawnParameters SpawnParameters;
	ABaseRoad* Road = GetWorld()->SpawnActor<ABaseRoad>(SelectedRoad, SpawnLocation, SpawnRotation, SpawnParameters);
	Road->SetSpawnRef(this);
	SpawnedRoads.Add(Road);
}