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

	FInventorySlot NewVehicle = *GameInstance->GetInventoryInstance().Find(GameInstance->GetVehicleIntInstance());
	NewVehicle.VehicleCustomization.BodyPaint = NewMaterial;
	PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleIntInstance(), NewVehicle);
}

void UUpgradeWidget::SelectWheels(UStaticMesh* NewWheels)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	AVehiclePawn* Vehicle = GarageRef->GetCurrentCatalogVehicle();

	if (Vehicle)
	{
		Vehicle->GetWheelFL()->SetStaticMesh(NewWheels);
		Vehicle->GetWheelFR()->SetStaticMesh(NewWheels);
		Vehicle->GetWheelRL()->SetStaticMesh(NewWheels);
		Vehicle->GetWheelRR()->SetStaticMesh(NewWheels);
	}
}

bool UUpgradeWidget::BuyWheels(UStaticMesh* NewWheels, int32 Price)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (GameInstance->GetBasicCurrencyInstance() >= Price)
	{
		PlayerController->DecreaseBasicCurrency(Price);

		FInventorySlot NewVehicle = *GameInstance->GetInventoryInstance().Find(GameInstance->GetVehicleIntInstance());
		NewVehicle.VehicleCustomization.Wheel = NewWheels;
		PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleIntInstance(), NewVehicle);

		return true;
	}

	return false;
}

void UUpgradeWidget::Return()
{
	GarageRef->SetWidgetState(EWidgetState::EWS_Shop);
}
