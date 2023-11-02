#include "OutrunCopsGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "BaseGameInstance.h"
#include "BasePlayerController.h"
#include "InventoryComponent.h"


AOutrunCopsGameModeBase::AOutrunCopsGameModeBase()
{

}

void AOutrunCopsGameModeBase::BeginPlay()
{
	// Setting Vehicle
	Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetInventory()->SetVehicleInventory(Cast<UBaseGameInstance>(GetGameInstance())->GetPlayerInventory_Inst());
	// Setting Basic Currency
	Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetPlayerBasicCurrency(Cast<UBaseGameInstance>(GetGameInstance())->GetPlayerBasicCurrency_Inst());



}