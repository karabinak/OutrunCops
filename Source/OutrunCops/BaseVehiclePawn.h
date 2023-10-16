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


private:

	// TO DO VEHICLE WIDGET COMPONENT

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

public:
};
