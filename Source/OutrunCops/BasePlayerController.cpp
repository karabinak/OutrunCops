

#include "InventoryComponent.h"
#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

}
