

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Enemy.generated.h"

class AVehiclePawn;
class USphereComponent;
class AGameplayGamemode;


UCLASS()
class OUTRUNCOPS_API AEnemy : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:

	AEnemy();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StopOverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void AIMovement();

	void DistanceFromPlayer();


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	AVehiclePawn* PlayerPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	AGameplayGamemode* Gamemode;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USphereComponent* ArrestedZone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float DestroyDistance = 8000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float SpawnForce = 3000000.f;

	// Vehicle Parts
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelFL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelFR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrontBumper;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Siren;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mirrors;

public:

};