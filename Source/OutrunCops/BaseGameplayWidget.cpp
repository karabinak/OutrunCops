#include "OutrunCopsGameModeGameplay.h"
#include "Kismet/GameplayStatics.h"

#include "BaseGameplayWidget.h"

void UBaseGameplayWidget::AddPauseToViewport()
{
	Cast<AOutrunCopsGameModeGameplay>(UGameplayStatics::GetGameMode(GetWorld()))->GetPauseWidget()->AddToViewport();
}
