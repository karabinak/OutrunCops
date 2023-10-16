
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "BaseMenuWidget.h"
#include "BaseShopWidget.h"
#include "BaseVehiclePawn.h"
#include "BasePlayerController.h"
#include "BaseGameInstance.h"
#include "InventoryComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


#include "BaseGarage.h"

ABaseGarage::ABaseGarage()
{
	PrimaryActorTick.bCanEverTick = true;

	Garage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Garage"));
	SetRootComponent(Garage);

	VehicleStand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_VehicleStand"));
	VehicleStand->SetupAttachment(Garage);

	GarageMainView = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	GarageMainView->SetupAttachment(GetRootComponent());

}

void ABaseGarage::BeginPlay()
{
	Super::BeginPlay();

	CreateMenuWidget();
	CreateShopWidget();

	if (MenuWidget && ShopWidget)
	{
		MenuWidget->AddToViewport();
		Cast<UBaseMenuWidget>(MenuWidget)->SetGarageRef(this);
		Cast<UBaseShopWidget>(ShopWidget)->SetGarageRef(this);
	}
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->SetViewTarget(this);
	}

	// PLACEHODER
	PlayerController->GetInventory()->AddToInventory(0, VehicleCatalog.Find(0)->Get());
	UBaseGameInstance* Instance = Cast<UBaseGameInstance>(GetGameInstance());
	Instance->SetCurrentVehicle(PlayerController->GetInventory()->GetFromInventory(0));

	SetPreviewVehicle(0);
}

void ABaseGarage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABaseVehiclePawn* ABaseGarage::SetPreviewVehicle(int32 CurrentValue)
{
	if (!PlayerController->GetInventory()->GetVehicleInventory().IsEmpty() && PlayerController->GetInventory()->GetVehicleInventory().Contains(CurrentValue))
	{
		if (CurrentCatalogVehicle)
		{
			CurrentCatalogVehicle->Destroy();
		}
		FVector Location = VehicleStand->GetSocketLocation(FName(TEXT("AttachVehicle")));
		FRotator Rotation = VehicleStand->GetSocketRotation(FName(TEXT("AttachVehicle")));
		FActorSpawnParameters SpawnParameters;
		CurrentCatalogVehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(PlayerController->GetInventory()->GetVehicleInventory().Find(CurrentValue)->Get(), Location, Rotation, SpawnParameters);
		CurrentCatalogVehicle->GetMesh()->SetSimulatePhysics(false);
		CurrentCatalogVehicle->AttachToComponent(VehicleStand, FAttachmentTransformRules::KeepRelativeTransform);
		return CurrentCatalogVehicle;
	}

	if (VehicleCatalog.Find(CurrentValue))
	{
		if (CurrentCatalogVehicle)
		{
			CurrentCatalogVehicle->Destroy();
		}
		FVector Location = VehicleStand->GetSocketLocation(FName(TEXT("AttachVehicle")));
		FRotator Rotation = VehicleStand->GetSocketRotation(FName(TEXT("AttachVehicle")));
		FActorSpawnParameters SpawnParameters;
		CurrentCatalogVehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(VehicleCatalog.Find(CurrentValue)->Get(), Location, Rotation, SpawnParameters);
		CurrentCatalogVehicle->GetMesh()->SetSimulatePhysics(false);
		CurrentCatalogVehicle->AttachToComponent(VehicleStand, FAttachmentTransformRules::KeepRelativeTransform);
		return CurrentCatalogVehicle;
	}

	return nullptr;
}

void ABaseGarage::CreateMenuWidget()
{
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	}
}

void ABaseGarage::CreateShopWidget()
{
	if (ShopWidgetClass)
	{
		ShopWidget = CreateWidget<UUserWidget>(GetWorld(), ShopWidgetClass);
	}
}

void ABaseGarage::SetWidgetState(EWidgetState ChangeWidgetState)
{
	WidgetState = ChangeWidgetState;

	switch (WidgetState)
	{
	case EWidgetState::EWS_Menu:

		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		MenuWidget->AddToViewport();
		break;


	case EWidgetState::EWS_Shop:

		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		ShopWidget->AddToViewport();
		break;


	case EWidgetState::EWS_MAX:
		break;
	}
}