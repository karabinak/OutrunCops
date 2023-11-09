#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "BaseVehiclePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;

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

	// Distance Varaibles

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	float Distance = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	FVector LastFrameVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Distance Calculation", meta = (AllowPrivateAccess = "true"))
	bool bCanCalculateDistance = false;

	// Car Parts
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WheelFL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WheelFR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WheelRL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WheelRR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FrontBumper;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RearBumper;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MirrorR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MirrorL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hood;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Trunk;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	bool bCanHit = true;

	FTimerHandle HitCooldownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float HitPoints = 200.f;

public:

	UFUNCTION()
	void ChangeCamera(float Axis);

	FORCEINLINE void SetCanCalculateDistance(bool CanCalculate) { bCanCalculateDistance = CanCalculate; }
};
