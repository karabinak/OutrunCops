#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "BaseVehiclePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class UStaticMeshComponent;
class AOutrunCopsGameModeGameplay;

UCLASS()
class OUTRUNCOPS_API ABaseVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:

	ABaseVehiclePawn();
	virtual void BeginPlay() override;
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
	void CalculatePoliceWasted();

	// TO DELETE
	void Interaction();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* VehicleWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	int32 Price = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	FName Name = TEXT("Polo");

	AOutrunCopsGameModeGameplay* Gamemode;

	// Distance Varaibles

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	float Distance = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	FVector LastFrameVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	bool bCanCalculateDistance = false;

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

	// Hitting

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	bool bCanHit = true;

	FTimerHandle HitCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float HitPoints = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float OnePartHitPoints = HitPoints / 6;

	int32 ActiveParts = 5;

	TArray<UStaticMeshComponent*> PartsToDetach;

	// Chasers

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 AmountOfChasersInSphere = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MinSpeedToGetWasted = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))

	float ElapsedTimeWasted = 0.f;

	FTimerHandle TimeToWasted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float TimeToGetWasted = 3.f;


public:

	UFUNCTION()
	void ChangeCamera(float Axis);

	FORCEINLINE void SetCanCalculateDistance(bool CanCalculate) { bCanCalculateDistance = CanCalculate; }
	FORCEINLINE float GetDistance() {return Distance; }
	FORCEINLINE int32 GetPrice() { return Price; }

	void SetAmountOfChasersInSphere(int32 Amount) { AmountOfChasersInSphere += Amount; }
};
