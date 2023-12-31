#include "VehicleWidget.h"

// Engine


// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"

void UVehicleWidget::NativeConstruct()
{
	VehicleRef = Cast<AVehiclePawn>(GetOwningPlayerPawn());
}
