#include "Kismet/GameplayStatics.h"

#include "BasePauseWidget.h"


void UBasePauseWidget::OpenMenuLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}