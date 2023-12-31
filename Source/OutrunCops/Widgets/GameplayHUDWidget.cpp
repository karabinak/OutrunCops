#include "GameplayHUDWidget.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/Gamemodes/GameplayGamemode.h"
#include "OutrunCops/Vehicles/VehiclePawn.h"


void UGameplayHUDWidget::NativeConstruct()
{
	PawnRef = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CustomConstruct();
}

void UGameplayHUDWidget::AddPauseToViewport()
{
	Cast<AGameplayGamemode>(UGameplayStatics::GetGameMode(GetWorld()))->GetPauseWidget()->AddToViewport();
}
