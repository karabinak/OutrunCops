
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VehicleWidget.generated.h"

class AVehiclePawn;

UCLASS()
class OUTRUNCOPS_API UVehicleWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	AVehiclePawn* VehicleRef;
};
