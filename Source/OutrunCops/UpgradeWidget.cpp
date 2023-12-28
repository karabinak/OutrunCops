#include "UpgradeWidget.h"

#include "BaseGameInstance.h"
#include "BasePlayerController.h"
#include "BaseVehiclePawn.h"
#include "BaseGarage.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"


void UUpgradeWidget::ChangeColor(UMaterial* NewMaterial)
{
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	ABaseVehiclePawn* Vehicle = GarageRef->GetCurrentCatalogVehicle();

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
	PlayerController->GetInventory()->AddToInventory(GameInstance->GetVehicleInt_Inst(), NewVehicle);
}

void UUpgradeWidget::Return()
{
	GarageRef->SetWidgetState(EWidgetState::EWS_Shop);
}
