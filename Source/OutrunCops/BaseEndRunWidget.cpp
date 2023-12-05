// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEndRunWidget.h"

#include "Kismet/GameplayStatics.h"

void UBaseEndRunWidget::OpenMenuLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
