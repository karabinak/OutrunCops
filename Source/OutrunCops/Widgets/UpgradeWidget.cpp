#include "UpgradeWidget.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Controllers/MyPlayerController.h"
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/Inventory/InventoryComponent.h"
#include "OutrunCops/Garage/Garage.h"


void UUpgradeWidget::ChangeColor(UMaterial* NewMaterial)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	AVehiclePawn* Vehicle = GarageRef->GetCurrentCatalogVehicle();

	if (Vehicle)
	{
		Vehicle->GetMesh()->SetMaterial(0, NewMaterial);

		TArray<UStaticMeshComponent*> VehicleParts = Vehicle->GetPartsToDetach();
		for (int i = 0; i < VehicleParts.Num(); i++)
		{
			if (VehicleParts[i])
			{
				VehicleParts[i]->SetMaterial(0, NewMaterial);
			}
		}
	}

	FInventorySlot NewVehicle;
	NewVehicle.VehicleClass = Vehicle->GetClass();
	NewVehicle.VehicleCustomization.BodyPaint = NewMaterial;
	NewVehicle.VehicleUpgrades.MaxTorque = 60.f;
	PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleInt_Inst(), NewVehicle);
}

void UUpgradeWidget::Return()
{
	GarageRef->SetWidgetState(EWidgetState::EWS_Shop);
}
