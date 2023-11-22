// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShopWidget.h"

#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BaseGarage.h"
#include "BasePlayerController.h"
#include "BaseVehiclePawn.h"

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
	return true;
}

bool UBaseShopWidget::SubtractVehicleInt()
{
	if (VehicleInt - 1 < 0) return false;

	VehicleInt--;
	return true;
}

void UBaseShopWidget::BuyVehicle()
{
	if (PlayerControllerRef)
	{
		if (PlayerControllerRef->GetPlayerBasicCurrency() >= GarageRef->GetCurrentCatalogVehicle()->GetPrice())
		{
			PlayerControllerRef->SubtractBasicCurrency(GarageRef->GetCurrentCatalogVehicle()->GetPrice());
<<<<<<< HEAD
			PlayerControllerRef->GetInventory()->AddToInventory(VehicleInt, GarageRef->GetCurrentCatalogVehicle());
=======
>>>>>>> parent of 82e9278 (Save)
		}
		else
		{
			// NO MONEY?
			GEngine->AddOnScreenDebugMessage(1, -1.f, FColor::Red, FString::Printf(TEXT("No Bitches??")));
		}
	}
}

void UBaseShopWidget::ChangeMaterial()
{
	GarageRef->GetCurrentCatalogVehicle()->GetMesh()->SetMaterial(0, Material);
	PlayerControllerRef->GetInventory()->AddToInventory(VehicleInt, GarageRef->GetCurrentCatalogVehicle());
}