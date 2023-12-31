
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

class UBoxComponent;
class ARoadSpawner;
class APickup;

UCLASS()
class OUTRUNCOPS_API ARoad : public AActor
{
	GENERATED_BODY()

public:
	ARoad();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSpawnerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraChangeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ChangeCameraEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SpawnHealthPickup();


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Road;

	//Spawner Trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpawnerTrigger;

	//CameraChange Trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CameraTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ARoadSpawner* SpawnerRef;

	//CameraChange
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float CameraChangeValue = 0.f;

	// Other
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APickup> Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	float ChanceToSpawnPickup = 0.1f;

public:

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Road; }
	FORCEINLINE void SetSpawnRef(ARoadSpawner* Spawner) { SpawnerRef = Spawner; }

};