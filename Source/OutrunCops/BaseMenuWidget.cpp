#include "BaseMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "BaseGameInstance.h"
#include "BasePlayerController.h"
#include "InventoryComponent.h"

void UBaseMenuWidget::NativeConstruct()
{
	
}

void UBaseMenuWidget::OpenDesertLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Desert"));
}
