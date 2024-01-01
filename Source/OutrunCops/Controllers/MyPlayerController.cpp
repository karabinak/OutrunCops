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

void AMyPlayerController::AddBasicCurrency(int32 Currency)
{
	PlayerBasicCurrency += Currency;
	Cast<UMyGameInstance>(GetGameInstance())->SetBasicCurrencyInstance(PlayerBasicCurrency);
	Cast<UMyGameInstance>(GetGameInstance())->SaveGame();
}

void AMyPlayerController::DecreaseBasicCurrency(int32 Currency)
{
	if (PlayerBasicCurrency - Currency <= 0)
	{
		PlayerBasicCurrency = 0;
	}
	else
	{
		PlayerBasicCurrency = PlayerBasicCurrency - Currency;
	}
	Cast<UMyGameInstance>(GetGameInstance())->SetBasicCurrencyInstance(PlayerBasicCurrency);
	Cast<UMyGameInstance>(GetGameInstance())->SaveGame();
}
