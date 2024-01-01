#include "RoadSpawner.h"

// Engine


// Custom
#include "OutrunCops/Roads/Road.h"

//////////////////////////////////////////////////////


ARoadSpawner::ARoadSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ARoadSpawner::BeginPlay()
{
	Super::BeginPlay();

	BeginRoadPattern();
}

void ARoadSpawner::BeginRoadPattern()
{
	SpawnRoad(0, true);
	SpawnRoad(0, true);
	SpawnRoad(5, true);
	SpawnRoad(0, true);
	SpawnRoad(0, true);
	SpawnRoad(0, true);
	SpawnBarricade();
}

void ARoadSpawner::SpawnRoad(int32 RoadNumber, bool CustomRoad)
{
	RandomRoadInt(CustomRoad, RoadNumber);

	UClass* SelectedRoad = RoadCollection[RandRoad];

	GetSocketTransform();
	DestroyLastRoad();
	CreateRoad(SelectedRoad);
	if (!CustomRoad)
	{
		SpawnBarricade();
	}
}

void ARoadSpawner::RandomRoadInt(bool CustomRoad, const int32& RoadNumber)
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
}

void ARoadSpawner::CreateRoad(UClass* SelectedRoad)
{
	FActorSpawnParameters SpawnParameters;
	ARoad* Road = GetWorld()->SpawnActor<ARoad>(SelectedRoad, SpawnLocation, SpawnRotation, SpawnParameters);
	Road->SetSpawner(this);
	SpawnedRoads.Add(Road);
}

void ARoadSpawner::DestroyLastRoad()
{
	if (SpawnedRoads.Num() >= MaxSpawnedRoads)
	{
		SpawnedRoads[0]->Destroy();
		SpawnedRoads.RemoveAt(0);
	}
}

void ARoadSpawner::GetSocketTransform()
{
	if (!SpawnedRoads.IsEmpty())
	{
		FTransform SocketTransform = SpawnedRoads[SpawnedRoads.Num() - 1]->GetMesh()->GetSocketTransform("AttachSocket");
		SpawnLocation = SocketTransform.GetLocation();
		SpawnRotation = SocketTransform.GetRotation().Rotator();
	}
}

void ARoadSpawner::SpawnBarricade()
{
	if (SpawnedBarricade)
	{
		SpawnedBarricade->Destroy();
		SpawnedBarricade = nullptr;
	}

	if (SpawnedRoads[1])
	{
		FActorSpawnParameters SpawnerParametersBarricade;
		ARoad* RoadToSpawnBarricade = SpawnedRoads[1];
		UClass* BarricadeClass = Barricade.Get();
		SpawnedBarricade = GetWorld()->SpawnActor<AActor>(BarricadeClass, RoadToSpawnBarricade->GetActorLocation(), RoadToSpawnBarricade->GetActorRotation(), SpawnerParametersBarricade);
	}
}