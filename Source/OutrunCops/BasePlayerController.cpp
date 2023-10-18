

#include "InventoryComponent.h"
#include "BaseGameInstance.h"
#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	
}

void ABasePlayerController::AddBasicCurrency(int32 BasicCurrency)
{
	PlayerBasicCurrency += BasicCurrency;
	Cast<UBaseGameInstance>(GetGameInstance())->SetPlayerBasicCurrency_Inst(PlayerBasicCurrency);
}

void ABasePlayerController::SubtractBasicCurrency(int32 BasicCurrency)
{
	if (PlayerBasicCurrency - BasicCurrency <= 0)
	{
		PlayerBasicCurrency = 0;
	}
	else
	{
		PlayerBasicCurrency = PlayerBasicCurrency - BasicCurrency;
	}
	Cast<UBaseGameInstance>(GetGameInstance())->SetPlayerBasicCurrency_Inst(PlayerBasicCurrency);
}
