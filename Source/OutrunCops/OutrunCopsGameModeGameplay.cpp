#include "OutrunCopsGameModeGameplay.h"

#include "BaseVehiclePawn.h"
#include "BaseGameInstance.h"
#include "BaseVehiclePawn.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerController.h"
#include "InventoryComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "BaseEnemy.h"

AOutrunCopsGameModeGameplay::AOutrunCopsGameModeGameplay()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AOutrunCopsGameModeGameplay::BeginPlay()
{
	Super::BeginPlay();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());

	FActorSpawnParameters ActorSpawnParameters;
	BaseVehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(GameInstance->GetPlayerVehicle_Inst(), FVector(500.f, 0.f, 15.f), FRotator(0.f, 0.f, 0.f), ActorSpawnParameters);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(BaseVehicle);

	Cast<ABasePlayerController>(BaseVehicle->GetController())->SetPlayerBasicCurrency(GameInstance->GetPlayerBasicCurrency_Inst());
	GameInstance->LoadGame();

	//Cast<ABasePlayerController>(BaseVehicle->GetController())->GetInventory()->SetVehicleInventory(GameInstance->GetPlayerInventory_Inst());

	CreateGameplayWidget();
	CreatePauseWidget();
	CreateEndRunWidget();

	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
	if (BaseVehicle)
	{
		BaseVehicle->SetCanCalculateDistance(true);
	}
}

void AOutrunCopsGameModeGameplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AmountOfChasersInSphere > 0 && BaseVehicle->GetVehicleMovement()->GetForwardSpeedMPH() * 1.609344 <= MinSpeedToGetWasted && BaseVehicle->GetVehicleMovement()->GetForwardSpeedMPH() * 1.609344 >= -MinSpeedToGetWasted)
	{
		ElapsedTimeWasted = GetWorldTimerManager().GetTimerElapsed(TimeToWasted);
		if (!GetWorldTimerManager().IsTimerActive(TimeToWasted))
		{
			GetWorldTimerManager().SetTimer(TimeToWasted, this, &AOutrunCopsGameModeGameplay::EndRun, TimeToGetWasted);
		}
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Blue, FString::Printf(TEXT("TimeElapsed: %f"), ElapsedTimeWasted));
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimeToWasted);
		ElapsedTimeWasted = 0.f;
	}
}

void AOutrunCopsGameModeGameplay::SpawnPoliceCar()
{
	if (PoliceAmount < MaxPolice)
	{
		FActorSpawnParameters Spawnparameters;

		for (int i = 0; i < 5; i++)
		{
			ABaseEnemy* PoliceCar = GetWorld()->SpawnActor<ABaseEnemy>(BasicPoliceCar.Get(), PoliceSpawnTransform, Spawnparameters);
			if (PoliceCar)
			{
				SetPoliceAmount(1);
				PoliceCar = nullptr;
				return;
			}
			PoliceSpawnTransform.SetLocation(PoliceSpawnTransform.GetLocation() + FVector(-50.f, 0.f, 0.f));
		}
	}
}

void AOutrunCopsGameModeGameplay::SetAmountOfChasersInSphere(int32 Amount)
{
	AmountOfChasersInSphere += Amount;
}

void AOutrunCopsGameModeGameplay::CreateGameplayWidget()
{
	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UUserWidget>(GetWorld(), GameplayWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::CreatePauseWidget()
{
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::CreateEndRunWidget()
{
	if (EndRunWidgetClass)
	{
		EndRunWidget = CreateWidget<UUserWidget>(GetWorld(), EndRunWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::AddEndRunToViewport()
{
	if (EndRunWidget)
	{
		EndRunWidget->AddToViewport();
	}
}

void AOutrunCopsGameModeGameplay::EndRun()
{
	AddEndRunToViewport();
}
