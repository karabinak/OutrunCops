
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRoad.generated.h"

class UBoxComponent;
class ABaseSpawner;

UCLASS()
class OUTRUNCOPS_API ABaseRoad : public AActor
{
	GENERATED_BODY()

public:
	ABaseRoad();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSpawnerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraChangeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ChangeCameraEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


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
	ABaseSpawner* SpawnerRef;

	//CameraChange
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float CameraChangeValue = 0.f;

	// Others
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	bool bTunnel = false;

	// Organizaiton
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Assets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Organization", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Props;

public:

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Road; }
	FORCEINLINE void SetSpawnRef(ABaseSpawner* Spawner) { SpawnerRef = Spawner; }

};