#include "Kismet/GameplayStatics.h"

#include "BaseMenuWidget.h"

void UBaseMenuWidget::NativeConstruct()
{
	
}

void UBaseMenuWidget::OpenDesertLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Desert"));
}
