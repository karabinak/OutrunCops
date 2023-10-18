#include "Kismet/GameplayStatics.h"
#include "BaseGameInstance.h"
#include "BasePlayerController.h"
#include "InventoryComponent.h"
#include "BaseMenuWidget.h"

void UBaseMenuWidget::NativeConstruct()
{
	
}

void UBaseMenuWidget::OpenDesertLevel()
{
	//Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetInventory()->GetVehicleInventory();
	Cast<UBaseGameInstance>(GetGameInstance())->SetPlayerInventory_Inst(Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetInventory()->GetVehicleInventory());
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Desert"));
}
