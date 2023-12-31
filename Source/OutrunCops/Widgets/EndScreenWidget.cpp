#include "EndScreenWidget.h"

// Engine
#include "Kismet/GameplayStatics.h"



void UEndScreenWidget::OpenMenuLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
