
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

class UBoxComponent;
class ARoadSpawner;
class APickup;
class AVehiclePawn;
class AGameplayGamemode;
//class AGeometryCollectionActor;

UCLASS()
class OUTRUNCOPS_API ARoad : public AActor
{
	GENERATED_BODY()

public:
	ARoad();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	AVehiclePawn* PlayerPawn;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSpawnerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraChangeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ChangeCameraEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SpawnPickup();

	void SpawnPoliceBarricade();


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ARoadSpawner* Spawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	AGameplayGamemode* Gamemode;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Road;

	//Spawner Trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpawnerTrigger;

	//CameraChange Trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CameraTrigger;


	// CameraChange
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float CameraChangeValue = 0.f;

	// Pickups
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APickup> Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	float ChanceToSpawnPickup = 0.05f;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<AGeometryCollectionActor> PoliceBarricade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> PoliceBarricade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float ChanceToSpawnPoliceBarricade = 0.f;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	bool bTunnel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USceneComponent* PickupSpawnLocation;

	// Organizaiton
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Assets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Props;

public:

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Road; }
	FORCEINLINE void SetSpawner(ARoadSpawner* SpawnerRef) { Spawner = SpawnerRef; }

};