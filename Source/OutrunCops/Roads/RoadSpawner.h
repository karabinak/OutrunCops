
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadSpawner.generated.h"

class ARoad;

USTRUCT(BlueprintType)
struct FRoadPatterns
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoadPatterns", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ARoad>> RoadPatterns;
};

UCLASS()
class OUTRUNCOPS_API ARoadSpawner : public AActor
{
	GENERATED_BODY()

public:
	ARoadSpawner();

protected:
	virtual void BeginPlay() override;

	void BeginRoadPattern();

	void SpawnBarricade();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<ARoad>> RoadCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TArray<ARoad*> SpawnedRoads;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 MaxSpawnedRoads = 8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 RandRoad = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 LastRoadSpawned = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	FVector SpawnLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	FRotator SpawnRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> BlockingActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"))
	AActor* SpawnedBlockingActor;

	// Road Pattern Spawner
	bool bActivePattern = true;

	bool bBeginPattern = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoadPatterns", meta = (AllowPrivateAccess = "true"))
	float PatternRoadChance = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoadPatterns", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FRoadPatterns> RoadPatterns;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoadPatterns", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ARoad>> ActiveRoadPattern;


public:

	void SpawnRoad(int32 RoadNumber = 0, bool CustomRoad = false);
	void RandomRoadInt(bool CustomRoad, const int32& RoadNumber);
	void CreateRoad(UClass* SelectedRoad);
	void DestroyLastRoad();
	void GetSocketTransform();
	TArray<ARoad*> GetSpawnedRoads() { return SpawnedRoads; }
};
