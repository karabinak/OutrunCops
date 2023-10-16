
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

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Road;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpawnerTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ABaseSpawner* SpawnerRef;

public:

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Road; }
	FORCEINLINE void SetSpawnRef(ABaseSpawner* Spawner) { SpawnerRef = Spawner; }

};