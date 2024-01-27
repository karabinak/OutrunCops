#include "UpgradeWidget.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Controllers/MyPlayerController.h"
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/Inventory/InventoryComponent.h"
#include "OutrunCops/Garage/Garage.h"


void UUpgradeWidget::SelectPaint(UMaterial* NewMaterial, int32 Value)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	AVehiclePawn* Vehicle = GarageRef->GetCurrentCatalogVehicle();

	if (Vehicle)
	{
		Vehicle->GetMesh()->SetMaterial(0, NewMaterial);

		TArray<UStaticMeshComponent*> VehicleParts = Vehicle->GetAllVehicleParts();
		for (int i = 0; i < VehicleParts.Num(); i++)
		{
			if (VehicleParts[i])
			{
				VehicleParts[i]->SetMaterial(0, NewMaterial);
			}
		}
	}
	if (PlayerController->GetInventory()->IsInPaintsInventoryInventory(Value))
	{
		FInventorySlot NewVehicle = *GameInstance->GetInventoryInstance().Find(GameInstance->GetVehicleIntInstance());
		NewVehicle.VehicleCustomization.BodyPaint = NewMaterial;
		PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleIntInstance(), NewVehicle);
		PlayerController->GetInventory()->AddToPaintsInventoryInventory(Value, NewMaterial);
	}
}

bool UUpgradeWidget::BuyPaint(UMaterial* NewMaterial, int32 Price, int32 Value)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (GameInstance->GetBasicCurrencyInstance() >= Price && !PlayerController->GetInventory()->IsInPaintsInventoryInventory(Value))
	{
		PlayerController->DecreaseBasicCurrency(Price);

		FInventorySlot NewVehicle = *GameInstance->GetInventoryInstance().Find(GameInstance->GetVehicleIntInstance());
		NewVehicle.VehicleCustomization.BodyPaint = NewMaterial;
		PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleIntInstance(), NewVehicle);
		PlayerController->GetInventory()->AddToPaintsInventoryInventory(Value, NewMaterial);

		return true;
	}

	return false;
}

void UUpgradeWidget::SelectWheels(UStaticMesh* NewWheels, int32 Value)
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
	if (PlayerController->GetInventory()->IsInWheelsInventory(Value))
	{
		FInventorySlot NewVehicle = *GameInstance->GetInventoryInstance().Find(GameInstance->GetVehicleIntInstance());
		NewVehicle.VehicleCustomization.Wheel = NewWheels;
		PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleIntInstance(), NewVehicle);
		PlayerController->GetInventory()->AddToWheelsInventory(Value, NewWheels);
	}
}

bool UUpgradeWidget::BuyWheels(UStaticMesh* NewWheels, int32 Price, int32 Value)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (GameInstance->GetBasicCurrencyInstance() >= Price && !PlayerController->GetInventory()->IsInWheelsInventory(Value))
	{
		PlayerController->DecreaseBasicCurrency(Price);

		FInventorySlot NewVehicle = *GameInstance->GetInventoryInstance().Find(GameInstance->GetVehicleIntInstance());
		NewVehicle.VehicleCustomization.Wheel = NewWheels;
		PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleIntInstance(), NewVehicle);
		PlayerController->GetInventory()->AddToWheelsInventory(Value, NewWheels);

		return true;
	}

	return false;
}

void UUpgradeWidget::Return()
{
	GarageRef->SetWidgetState(EWidgetState::EWS_Shop);
}
