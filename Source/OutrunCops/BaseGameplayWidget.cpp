#include "BaseGameplayWidget.h"

#include "OutrunCopsGameModeGameplay.h"
#include "Kismet/GameplayStatics.h"
#include "BaseVehiclePawn.h"

void UBaseGameplayWidget::NativeConstruct()
{
	PawnRef = Cast<ABaseVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UBaseGameplayWidget::AddPauseToViewport()
{
	Cast<AOutrunCopsGameModeGameplay>(UGameplayStatics::GetGameMode(GetWorld()))->GetPauseWidget()->AddToViewport();
}
