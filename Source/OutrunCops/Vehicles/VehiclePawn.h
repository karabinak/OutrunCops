#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "VehiclePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class UStaticMeshComponent;
class UChaosWheeledVehicleMovementComponent;
class USplineComponent;
class UMatineeCameraShake;

UENUM(BlueprintType)
enum class EVehicleState : uint8
{
	EVS_Inactive UMETA(DisplayName = "CantPlay"),
	EVS_Active UMETA(DisplayName = "Playing"),
};

UCLASS()
class OUTRUNCOPS_API AVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:

	AVehiclePawn();
	virtual void BeginPlay() override;
	void LoadVehicleMaterial();
	void PopulateMeshArray();
	virtual void Tick(float DeltaSeconds) override;

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	void Throttle(float AxisValue);
	void Brake(float AxisValue);
	void Steer(float AxisValue);
	void CalculateDistance();
	void DetachComponent(UStaticMeshComponent* CarPart);
	void AttachComponent(UStaticMeshComponent* CarPart);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ResetCanHit();

	void SelfDrive();

	// TO DELETE
	void Interaction();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UChaosWheeledVehicleMovementComponent* EngineRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMatineeCameraShake> CameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* VehicleWidget;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	int32 Price = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	FName Name = TEXT("Polo");

	// Distance Varaibles

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	float Distance = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	FVector LastFrameVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	bool bCanCalculateDistance = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	bool bCanDrive = false;

	// Car Parts
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
	UStaticMeshComponent* RearBumper;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MirrorR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MirrorL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Hood;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Trunk;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	bool bCanHit = true;

	FTimerHandle HitCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float HitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float OnePartHitPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 ActiveParts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> PartsToDetach;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	FVector GarageSpawnLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float SpringArmBaseLenght = 1700.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	FRotator SpringArmLastRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	EVehicleState VehicleState = EVehicleState::EVS_Inactive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineComponent;


public:

	UFUNCTION()
	void ChangeCamera(float ChangeValue, bool Tunnel);
	UFUNCTION()
	void EndChangCamera(bool Tunnel);

	void SetVehicleState(EVehicleState NewVehicleState);

	void PathDriving(USplineComponent* SplineComp);

	void AddHealth(float HealthAmount);
	FORCEINLINE UCameraComponent* GetCamera() { return Camera; }
	FORCEINLINE void SetCanCalculateDistance(bool CanCalculate) { bCanCalculateDistance = CanCalculate; }
	FORCEINLINE void SetLastFrameVector(FVector NewLastFrameVector) { LastFrameVector = NewLastFrameVector; }
	FORCEINLINE void SetDistance(float NewDistance) { Distance = NewDistance; }
	FORCEINLINE float GetDistance() { return Distance; }
	FORCEINLINE int32 GetPrice() { return Price; }
	FORCEINLINE float GetHitPoints() { return HitPoints; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE TArray<UStaticMeshComponent*> GetPartsToDetach() { return PartsToDetach; }
	FORCEINLINE FVector GetGarageSpawnLocation() { return GarageSpawnLocation; }
};
