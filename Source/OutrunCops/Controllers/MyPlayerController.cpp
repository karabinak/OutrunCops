#include "MyPlayerController.h"

// Engine


// Custom
#include "OutrunCops/Inventory/InventoryComponent.h"
#include "OutrunCops/GameInstance/MyGameInstance.h"

//////////////////////////////////////////////////////

AMyPlayerController::AMyPlayerController()
{
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	
}

void AMyPlayerController::AddBasicCurrency(int32 BasicCurrency)
{
	PlayerBasicCurrency += BasicCurrency;
	Cast<UMyGameInstance>(GetGameInstance())->SetPlayerBasicCurrency_Inst(PlayerBasicCurrency);
	Cast<UMyGameInstance>(GetGameInstance())->SaveGame();
}

void AMyPlayerController::SubtractBasicCurrency(int32 BasicCurrency)
{
	if (PlayerBasicCurrency - BasicCurrency <= 0)
	{
		PlayerBasicCurrency = 0;
	}
	else
	{
		PlayerBasicCurrency = PlayerBasicCurrency - BasicCurrency;
	}
	Cast<UMyGameInstance>(GetGameInstance())->SetPlayerBasicCurrency_Inst(PlayerBasicCurrency);
	Cast<UMyGameInstance>(GetGameInstance())->SaveGame();
}
