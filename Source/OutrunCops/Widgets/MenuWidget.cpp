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

	PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	AmountOfVehiclesInCatalog = Garage->GetVehicleCatalog().Num();

	VehicleInt = GameInstance->GetVehicleIntInstance();
}

void UMenuWidget::SaveCurrentVehicleInt(int32 CurrentVehicle)
{
	GameInstance->SetVehicleIntInstance(CurrentVehicle);
}

bool UMenuWidget::AddVehicleInt()
{
	if (VehicleInt + 1 > AmountOfVehiclesInCatalog - 1) return false;

	VehicleInt++;
	GameInstance->SetVehicleIntInstance(VehicleInt);
	return true;
}

bool UMenuWidget::SubtractVehicleInt()
{
	if (VehicleInt - 1 < 0) return false;

	VehicleInt--;
	GameInstance->SetVehicleIntInstance(VehicleInt);
	return true;
}

void UMenuWidget::BuyVehicle()
{
	if (PC)
	{
		if (PC->GetPlayerBasicCurrency() >= Garage->GetCurrentCatalogVehicle()->GetPrice())
		{
			PC->DecreaseBasicCurrency(Garage->GetCurrentCatalogVehicle()->GetPrice());

			FInventorySlot Vehicle;
			Vehicle.VehicleClass = Garage->GetCurrentCatalogVehicle()->GetClass();
			Vehicle.VehicleUpgrades.MaxTorque = 60.f;
			Vehicle.VehicleCustomization.BodyPaint = Garage->GetCurrentCatalogVehicle()->GetMesh()->GetMaterial(0)->GetMaterial();

			PC->GetInventory()->AddToInventory(VehicleInt, Vehicle);
			
		}
		else
		{
			// NO MONEY?
			GEngine->AddOnScreenDebugMessage(1, -1.f, FColor::Red, FString::Printf(TEXT("No Bitches??")));
		}
	}
}

void UMenuWidget::OpenModifyVehicle()
{
	if (Garage)
	{
		Garage->SetWidgetState(EWidgetState::EWS_Upgrade);
	}
}
