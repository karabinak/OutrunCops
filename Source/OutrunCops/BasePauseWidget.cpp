#include "BasePauseWidget.h"


#include "Kismet/GameplayStatics.h"


void UBasePauseWidget::OpenMenuLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}