#include "Garage.h"

// Engine
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/Inventory/InventoryComponent.h"
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Controllers/MyPlayerController.h"
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/Widgets/UpgradeWidget.h"
#include "OutrunCops/Widgets/MenuWidget.h"
#include "OutrunCops/Widgets/LevelSelectorWidget.h"

//////////////////////////////////////////////////////

AGarage::AGarage()
{
	PrimaryActorTick.bCanEverTick = true;

	Garage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Garage"));
	SetRootComponent(Garage);

	VehicleStand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_VehicleStand"));
	VehicleStand->SetupAttachment(Garage);

	GarageMainView = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	GarageMainView->SetupAttachment(GetRootComponent());

}

void AGarage::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	BeginCameraView();
	WidgetSettings();

	GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimer, this, &AGarage::DelayedBeginPlayFunc, 0.001f);
}

void AGarage::BeginCameraView()
{
	if (PC)
	{
		PC->SetViewTarget(this);
	}
}

void AGarage::WidgetSettings()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	CreateShopWidget();
	CreateLevelSelector();
	CreateUpgradeWidget();
	if (ShopWidget && LevelSelectorWidget && UpgradeWidget)
	{
		Cast<UMenuWidget>(ShopWidget)->SetGarageRef(this);
		Cast<ULevelSelectorWidget>(LevelSelectorWidget)->SetGarageRef(this);
		Cast<UUpgradeWidget>(UpgradeWidget)->SetGarageRef(this);
		ShopWidget->AddToViewport();
	}
}

void AGarage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AVehiclePawn* AGarage::SetPreviewVehicle(int32 VehicleValue)
{
	bool IsInInventory = PC->GetInventory()->GetInventory().Contains(VehicleValue);
	bool IsNotEmpty = !PC->GetInventory()->GetInventory().IsEmpty();

	// Vehicle From Player Inventory ( if purchased )
	if (IsNotEmpty && IsInInventory)
	{
		DestroyPreviousVehicle();
		SpawnNewVehicle(VehicleValue, IsInInventory);
		UMenuWidget* ShopCast = Cast<UMenuWidget>(ShopWidget);

		return CurrentCatalogVehicle;
	}

	// Vehicle From Catalog ( not purchased )
	if (VehicleCatalog.Find(VehicleValue))
	{
		DestroyPreviousVehicle();
		SpawnNewVehicle(VehicleValue, IsInInventory);
		UMenuWidget* ShopCast = Cast<UMenuWidget>(ShopWidget);

		return CurrentCatalogVehicle;
	}
	return CurrentCatalogVehicle;
}

void AGarage::DestroyPreviousVehicle()
{
	if (CurrentCatalogVehicle)
	{
		CurrentCatalogVehicle->Destroy();
	}
}

void AGarage::SpawnNewVehicle(int32 VehicleValue, bool IsInInventory)
{
	FVector Location = VehicleStand->GetSocketLocation(FName(TEXT("AttachVehicle")));
	FRotator Rotation = VehicleStand->GetSocketRotation(FName(TEXT("AttachVehicle")));
	FActorSpawnParameters SpawnParameters;
	if (IsInInventory)
	{
		CurrentCatalogVehicle = GetWorld()->SpawnActor<AVehiclePawn>(PC->GetInventory()->GetInventory().Find(VehicleValue)->VehicleClass.Get(), Location, Rotation, SpawnParameters);
	//UE_LOG(LogTemp, Warning, TEXT("True"));
	}
	else
	{
		CurrentCatalogVehicle = GetWorld()->SpawnActor<AVehiclePawn>(VehicleCatalog.Find(VehicleValue)->Get(), Location, Rotation, SpawnParameters);
	}

	CurrentCatalogVehicle->GetMesh()->SetSimulatePhysics(false);
	CurrentCatalogVehicle->AttachToComponent(VehicleStand, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentCatalogVehicle->SetActorRelativeLocation(CurrentCatalogVehicle->GetGarageSpawnLocation());
}

void AGarage::CreateShopWidget()
{
	if (ShopWidgetClass)
	{
		ShopWidget = CreateWidget<UUserWidget>(GetWorld(), ShopWidgetClass);
	}
}

void AGarage::CreateLevelSelector()
{
	if (LevelSelectorClass)
	{
		LevelSelectorWidget = CreateWidget<UUserWidget>(GetWorld(), LevelSelectorClass);
	}
}

void AGarage::CreateUpgradeWidget()
{
	if (UpgradeWidgetClass)
	{
		UpgradeWidget = CreateWidget<UUserWidget>(GetWorld(), UpgradeWidgetClass);
	}
}

void AGarage::DelayedBeginPlayFunc()
{
	SetPreviewVehicle(Cast<UMyGameInstance>(GetGameInstance())->GetVehicleIntInstance());
}

void AGarage::SetWidgetState(EWidgetState ChangeWidgetState)
{
	WidgetState = ChangeWidgetState;

	switch (WidgetState)
	{
	case EWidgetState::EWS_Shop:

		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		ShopWidget->AddToViewport();
		break;

	case EWidgetState::EWS_Upgrade:
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		OpenUpgrade();

	case EWidgetState::EWS_MAX:
		break;
	}
}

void AGarage::OpenLevelSelector()
{
	if (LevelSelectorWidget)
	{
		LevelSelectorWidget->AddToViewport();
	}
}

void AGarage::OpenUpgrade()
{
	if (UpgradeWidgetClass)
	{
		UpgradeWidget->AddToViewport();
	}
}

void AGarage::RemoveLevelSelector()
{
	if (LevelSelectorWidget)
	{
		LevelSelectorWidget->RemoveFromViewport();
	}
}
