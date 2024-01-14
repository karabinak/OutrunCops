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
	SpawnRoad();
	SpawnRoad();
	SpawnRoad();
	SpawnRoad();
	SpawnRoad();
	SpawnRoad();
	SpawnBarricade();
}

void ARoadSpawner::SpawnRoad(int32 RoadNumber, bool CustomRoad)
{
	if (bActivePattern)
	{
		if (bBeginPattern)
		{
			if (ActiveRoadPattern.IsEmpty())
			{
				/*
						Index 0 is a begin pattern ( ONLY ) !!
				*/

				ActiveRoadPattern = RoadPatterns.Find(0)->RoadPatterns;
			}

			UClass* SelectedRoad = ActiveRoadPattern[0];

			GetSocketTransform();
			DestroyLastRoad();
			CreateRoad(SelectedRoad);

			ActiveRoadPattern.RemoveAt(0);

			if (ActiveRoadPattern.IsEmpty())
			{
					bBeginPattern = false;
					bActivePattern = false;
			}
		}
		else
		{
			if (ActiveRoadPattern.IsEmpty())
			{
				int RandInt = FMath::RandRange(1, RoadPatterns.Num() - 1);
				ActiveRoadPattern = RoadPatterns.Find(RandInt)->RoadPatterns;
			}

			UClass* SelectedRoad = ActiveRoadPattern[0];

			GetSocketTransform();
			DestroyLastRoad();
			CreateRoad(SelectedRoad);

			ActiveRoadPattern.RemoveAt(0);

			if (ActiveRoadPattern.IsEmpty())
			{
				bActivePattern = false;
			}
		}
		return;
	}


	RandomRoadInt(CustomRoad, RoadNumber);

	UClass* SelectedRoad = RoadCollection[RandRoad];

	GetSocketTransform();
	DestroyLastRoad();
	CreateRoad(SelectedRoad);
	if (!CustomRoad)
	{
		SpawnBarricade();
	}

	// Active Pattern by chance
	if (!bActivePattern)
	{
		if (PatternRoadChance >= FMath::FRandRange(0.0f, 1.0f))
		{
			bActivePattern = true;
		}
	}
}

void ARoadSpawner::RandomRoadInt(bool CustomRoad, const int32& RoadNumber)
{
	RandRoad = FMath::RandRange(0, RoadCollection.Num() - 1);
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
}

void ARoadSpawner::CreateRoad(UClass* SelectedRoad)
{
	FActorSpawnParameters SpawnParameters;
	ARoad* Road = GetWorld()->SpawnActor<ARoad>(SelectedRoad, SpawnLocation, SpawnRotation, SpawnParameters);
	Road->SetSpawner(this);
	Road->SpawnPickup();
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
		TArray<FName> Sockets = SpawnedRoads[SpawnedRoads.Num() - 1]->GetMesh()->GetAllSocketNames();

		if (Sockets.Num() == 1)
		{
			FTransform SocketTransform = SpawnedRoads[SpawnedRoads.Num() - 1]->GetMesh()->GetSocketTransform(Sockets[0]);
			SpawnLocation = SocketTransform.GetLocation();
			SpawnRotation = SocketTransform.GetRotation().Rotator();
		}
		else
		{
			int32 RandomInt = FMath::RandRange(0, Sockets.Num() - 1);
			FTransform SocketTransform = SpawnedRoads[SpawnedRoads.Num() - 1]->GetMesh()->GetSocketTransform(Sockets[RandomInt]);
			SpawnLocation = SocketTransform.GetLocation();
			SpawnRotation = SocketTransform.GetRotation().Rotator();
		}

		// WORK IN PROGRESS CAMERA CHANGE 
		SpawnedRoads[SpawnedRoads.Num() - 1]->SetCameraChangeValue(SpawnRotation.Yaw);
	}
}

void ARoadSpawner::SpawnBarricade()
{
	if (SpawnedBlockingActor)
	{
		SpawnedBlockingActor->Destroy();
		SpawnedBlockingActor = nullptr;
	}

	if (SpawnedRoads[1])
	{
		FActorSpawnParameters SpawnerParametersBarricade;
		ARoad* RoadToSpawnBarricade = SpawnedRoads[1];
		UClass* BlockingActorClass = BlockingActor.Get();
		SpawnedBlockingActor = GetWorld()->SpawnActor<AActor>(BlockingActorClass, RoadToSpawnBarricade->GetActorLocation(), RoadToSpawnBarricade->GetActorRotation(), SpawnerParametersBarricade);
	}
}