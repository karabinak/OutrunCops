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
	SpawnRoad(5, true);
	SpawnRoad(0, true);
	SpawnRoad(0, true);
	SpawnRoad(0, true);
	SpawnBarricade();
}

void ABaseSpawner::SpawnRoad(int32 RoadNumber, bool CustomRoad)
{
	RandRoad = FMath::RandRange(0, RoadCollection.Num() - 2);
	if (CustomRoad)
	{
		RandRoad = RoadNumber;
	}
	else
	{
		while (RandRoad == LastRoadSpawned)
		{
			RandRoad = FMath::RandRange(0, RoadCollection.Num() - 2);
		}
	}
	LastRoadSpawned = RandRoad;

	UClass* SelectedRoad = RoadCollection[RandRoad];

	GetSocketTransform();
	DestroyLastRoad();
	CreateRoad(SelectedRoad);
	if (!CustomRoad)
	{
		SpawnBarricade();
	}
}

void ABaseSpawner::CreateRoad(UClass* SelectedRoad)
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

void ABaseSpawner::GetSocketTransform()
{
	if (!SpawnedRoads.IsEmpty())
	{
		FTransform SocketTransform = SpawnedRoads[SpawnedRoads.Num() - 1]->GetMesh()->GetSocketTransform("AttachSocket");
		SpawnLocation = SocketTransform.GetLocation();
		SpawnRotation = SocketTransform.GetRotation().Rotator();
	}
}

void ABaseSpawner::SpawnBarricade()
{
	if (SpawnedBarricade)
	{
		SpawnedBarricade->Destroy();
		SpawnedBarricade = nullptr;
	}

	if (SpawnedRoads[1])
	{
		FActorSpawnParameters SpawnerParametersBarricade;
		ABaseRoad* RoadToSpawnBarricade = SpawnedRoads[1];
		UClass* BarricadeClass = Barricade.Get();
		SpawnedBarricade = GetWorld()->SpawnActor<AActor>(BarricadeClass, RoadToSpawnBarricade->GetActorLocation(), RoadToSpawnBarricade->GetActorRotation(), SpawnerParametersBarricade);
	}
}