
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseVehicleWidget.generated.h"

class ABaseVehiclePawn;

UCLASS()
class OUTRUNCOPS_API UBaseVehicleWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	ABaseVehiclePawn* VehicleRef;
};
