#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "BaseVehiclePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInventoryComponent;

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

	// TEST

	void SpawnAndPossesPawn(int32 Selection);


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* Inventory;


public:
};
