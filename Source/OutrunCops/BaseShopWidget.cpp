// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShopWidget.h"

#include "Kismet/GameplayStatics.h"
#include "BasePlayerController.h"

void UBaseShopWidget::NativeConstruct()
{
	PC = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}