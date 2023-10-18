#include "Kismet/GameplayStatics.h"

#include "BaseGameplayWidget.h"

void UBaseGameplayWidget::OpenMenuLevel()
{
	//Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetInventory()->GetVehicleInventory();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
