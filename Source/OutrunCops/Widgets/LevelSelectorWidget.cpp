#include "LevelSelectorWidget.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom


void ULevelSelectorWidget::OpenLevel(FName LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}