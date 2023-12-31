
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadSpawner.generated.h"

class ARoad;

UCLASS()
class OUTRUNCOPS_API ARoadSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoadSpawner();

protected:
	virtual void BeginPlay() override;

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
	TSubclassOf<AActor> Barricade;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"))
	AActor* SpawnedBarricade;

public: 

	void SpawnRoad(int32 RoadNumber = 0, bool CustomRoad = false);
	void CreateRoad(UClass* SelectedRoad);
	void DestroyLastRoad();
	void GetSocketTransform();
};
