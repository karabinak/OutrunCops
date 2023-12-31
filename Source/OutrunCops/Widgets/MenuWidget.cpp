#include "MenuWidget.h"

// Engine
#include "Kismet/GameplayStatics.h"
#include "UpgradeWidget.h"

// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Controllers/MyPlayerController.h"
#include "OutrunCops/Inventory/InventoryComponent.h"
#include "OutrunCops/Garage/Garage.h"


void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerControllerRef = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameInstanceRef = Cast<UMyGameInstance>(GetGameInstance());

	AmountOfVehiclesInCatalog = GarageRef->GetVehicleCatalog().Num();

	VehicleInt = GameInstanceRef->GetVehicleInt_Inst();
}

void UMenuWidget::SaveCurrentVehicleInt(int32 CurrentVehicle)
{
	GameInstanceRef->SetVehicleInt_Inst(CurrentVehicle);
}

bool UMenuWidget::AddVehicleInt()
{
	if (VehicleInt + 1 > AmountOfVehiclesInCatalog - 1) return false;

	VehicleInt++;
	GameInstanceRef->SetVehicleInt_Inst(VehicleInt);
	return true;
}

bool UMenuWidget::SubtractVehicleInt()
{
	if (VehicleInt - 1 < 0) return false;

	VehicleInt--;
	GameInstanceRef->SetVehicleInt_Inst(VehicleInt);
	return true;
}

void UMenuWidget::BuyVehicle()
{
	if (PlayerControllerRef)
	{
		if (PlayerControllerRef->GetPlayerBasicCurrency() >= GarageRef->GetCurrentCatalogVehicle()->GetPrice())
		{
			PlayerControllerRef->SubtractBasicCurrency(GarageRef->GetCurrentCatalogVehicle()->GetPrice());

			FInventorySlot Vehicle;
			Vehicle.VehicleClass = GarageRef->GetCurrentCatalogVehicle()->GetClass();
			Vehicle.VehicleUpgrades.MaxTorque = 60.f;
			Vehicle.VehicleCustomization.BodyPaint = GarageRef->GetCurrentCatalogVehicle()->GetMesh()->GetMaterial(0)->GetMaterial();

			PlayerControllerRef->GetInventory()->AddToInventory(VehicleInt, Vehicle);
			Cast<UMyGameInstance>(GetGameInstance())->SetPlayerVehicle_Inst(PlayerControllerRef->GetInventory()->GetVehicleInventory().Find(VehicleInt)->VehicleClass);
			
		}
		else
		{
			// NO MONEY?
			GEngine->AddOnScreenDebugMessage(1, -1.f, FColor::Red, FString::Printf(TEXT("No Bitches??")));
		}
	}
}

//void UBaseShopWidget::ChangeVehicleColor()
//{
//	GarageRef->GetCurrentCatalogVehicle()->GetMesh()->SetMaterial(0, Material);
//
//	TArray<UStaticMeshComponent*> VehicleParts = GarageRef->GetCurrentCatalogVehicle()->GetPartsToDetach();
//	for (int i = 0; i < VehicleParts.Num(); i++)
//	{
//		if (VehicleParts[i])
//		{
//			VehicleParts[i]->SetMaterial(0, Material);
//		}
//	}
//
//	FInventorySlot Vehicle;
//	Vehicle.VehicleClass = GarageRef->GetCurrentCatalogVehicle()->StaticClass();
//	Vehicle.VehicleCustomization.BodyPaint = Material;
//	PlayerControllerRef->GetInventory()->AddToInventory(VehicleInt, Vehicle);
//}