// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelSelectorWidget.h"
#include "Kismet/GameplayStatics.h"


void ULevelSelectorWidget::OpenLevel(FName LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}