
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

class ABaseRoad;

UCLASS()
class OUTRUNCOPS_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseSpawner();

protected:
	virtual void BeginPlay() override;

	void SpawnBarricade();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<ABaseRoad>> RoadCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TArray<ABaseRoad*> SpawnedRoads;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 MaxSpawnedRoads = 9;

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
