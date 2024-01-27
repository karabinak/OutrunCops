#include "MainGamemode.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Controllers/MyPlayerController.h"
#include "OutrunCops/Inventory/InventoryComponent.h"

//////////////////////////////////////////////////////


AMainGamemode::AMainGamemode()
{

}

void AMainGamemode::BeginPlay()
{
	PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (PC && GameInstance)
	{
		PC->GetInventory()->SetInventory(GameInstance->GetInventoryInstance());
		PC->SetPlayerBasicCurrency(GameInstance->GetBasicCurrencyInstance());
		PC->GetInventory()->SetWheelsInventory(GameInstance->GetWheelsInventoryInstance());
		PC->GetInventory()->SetPaintsInventory(GameInstance->GetPaintsInventoryInstance());

		GameInstance->LoadGame();
		GameInstance->SaveGame();
	}
}