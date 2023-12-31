#include "PauseWidget.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom


void UPauseWidget::OpenMenuLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}