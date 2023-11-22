#include "BaseSpawner.h"

#include "BaseRoad.h"

ABaseSpawner::ABaseSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnRoad(0, true);
	SpawnRoad(0, true);
	SpawnRoad(0, true);
	SpawnRoad(0, true);
}

void ABaseSpawner::SpawnRoad(int32 RoadNumber, bool CustomRoad)
{
	if (CustomRoad)
	{
		RandRoad = RoadNumber;
	}
	else
	{
		while (RandRoad == LastRoadSpawned)
		{
			RandRoad = FMath::RandRange(0, RoadCollection.Num() - 1);
		}
	}
	LastRoadSpawned = RandRoad;

	UClass* SelectedRoad = RoadCollection[RandRoad];

	GetSpawnTransform();
	DestroyLastRoad();
	CreateNewRoad(SelectedRoad);
}

void ABaseSpawner::GetSpawnTransform()
{
	if (!SpawnedRoads.IsEmpty())
	{
		FTransform SocketTransform = SpawnedRoads[SpawnedRoads.Num() - 1]->GetMesh()->GetSocketTransform("AttachSocket");
		SpawnLocation = SocketTransform.GetLocation();
		SpawnRotation = SocketTransform.GetRotation().Rotator();
	}
}

void ABaseSpawner::CreateNewRoad(UClass* SelectedRoad)
{
	FActorSpawnParameters SpawnParameters;
	ABaseRoad* Road = GetWorld()->SpawnActor<ABaseRoad>(SelectedRoad, SpawnLocation, SpawnRotation, SpawnParameters);
	Road->SetSpawnRef(this);
	SpawnedRoads.Add(Road);
}

void ABaseSpawner::DestroyLastRoad()
{
	if (SpawnedRoads.Num() >= MaxSpawnedRoads)
	{
		SpawnedRoads[0]->Destroy();
		SpawnedRoads.RemoveAt(0);
	}
}
