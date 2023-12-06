// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShopWidget.h"

#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BaseGarage.h"
#include "BasePlayerController.h"
#include "BaseVehiclePawn.h"
#include "InventoryComponent.h"

void UBaseShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerControllerRef = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameInstanceRef = Cast<UBaseGameInstance>(GetGameInstance());

	AmountOfVehiclesInCatalog = GarageRef->GetVehicleCatalog().Num();

	VehicleInt = GameInstanceRef->GetVehicleInt_Inst();
}

void UBaseShopWidget::SaveCurrentVehicleInt(int32 CurrentVehicle)
{
	GameInstanceRef->SetVehicleInt_Inst(CurrentVehicle);
}

bool UBaseShopWidget::AddVehicleInt()
{
	if (VehicleInt + 1 > AmountOfVehiclesInCatalog - 1) return false;

	VehicleInt++;
	GameInstanceRef->SetVehicleInt_Inst(VehicleInt);
	return true;
}

bool UBaseShopWidget::SubtractVehicleInt()
{
	if (VehicleInt - 1 < 0) return false;

	VehicleInt--;
	GameInstanceRef->SetVehicleInt_Inst(VehicleInt);
	return true;
}

void UBaseShopWidget::BuyVehicle()
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
			
		}
		else
		{
			// NO MONEY?
			GEngine->AddOnScreenDebugMessage(1, -1.f, FColor::Red, FString::Printf(TEXT("No Bitches??")));
		}
	}
}

void UBaseShopWidget::ChangeVehicleColor()
{
	GarageRef->GetCurrentCatalogVehicle()->GetMesh()->SetMaterial(0, Material);

	TArray<UStaticMeshComponent*> VehicleParts = GarageRef->GetCurrentCatalogVehicle()->GetPartsToDetach();
	for (int i = 0; i < VehicleParts.Num(); i++)
	{
		if (VehicleParts[i])
		{
			VehicleParts[i]->SetMaterial(0, Material);
		}
	}

	FInventorySlot Vehicle;
	Vehicle.VehicleClass = GarageRef->GetCurrentCatalogVehicle()->GetClass();
	Vehicle.VehicleCustomization.BodyPaint = Material;
	PlayerControllerRef->GetInventory()->AddToInventory(VehicleInt, Vehicle);
}
