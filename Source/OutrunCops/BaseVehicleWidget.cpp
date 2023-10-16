#include "BaseVehicleWidget.h"

#include "BaseVehiclePawn.h"

void UBaseVehicleWidget::NativeConstruct()
{
	VehicleRef = Cast<ABaseVehiclePawn>(GetOwningPlayerPawn());
}
