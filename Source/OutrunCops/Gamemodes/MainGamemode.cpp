#include "MainGamemode.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Controllers/MyPlayerController.h"
#include "OutrunCops/Inventory/InventoryComponent.h"


AMainGamemode::AMainGamemode()
{

}

void AMainGamemode::BeginPlay()
{

	// Setting Vehicle
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetInventory()->SetVehicleInventory(Cast<UMyGameInstance>(GetGameInstance())->GetPlayerInventory_Inst());
	// Setting Basic Currency
	Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetPlayerBasicCurrency(Cast<UMyGameInstance>(GetGameInstance())->GetPlayerBasicCurrency_Inst());

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	GameInstance->SaveGame();
	GameInstance->LoadGame();

}