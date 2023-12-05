#include "BaseGarage.h"

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

	//// PLACEHODER
	//PlayerController->GetInventory()->AddToInventory(0, VehicleCatalog.Find(0)->Get());
	//UBaseGameInstance* Instance = Cast<UBaseGameInstance>(GetGameInstance());
	//Instance->SetCurrentVehicle(PlayerController->GetInventory()->GetFromInventory(0));

	SetPreviewVehicle(Cast<UBaseGameInstance>(GetGameInstance())->GetVehicleInt_Inst());
}

void ABaseGarage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABaseVehiclePawn* ABaseGarage::SetPreviewVehicle(int32 VehicleValue)
{
	bool IsInInventory = PlayerController->GetInventory()->GetVehicleInventory().Contains(VehicleValue);
	bool IsNotEmpty = !PlayerController->GetInventory()->GetVehicleInventory().IsEmpty();

	// Vehicle From Player Inventory ( if purchased )
	if (IsNotEmpty && IsInInventory)
	{
		DestroyPreviousVehicle();
		SpawnNewVehicle(VehicleValue, IsInInventory);
		return CurrentCatalogVehicle;
	}

	// Vehicle From Catalog ( not purchased )
	if (VehicleCatalog.Find(VehicleValue))
	{
		DestroyPreviousVehicle();
		SpawnNewVehicle(VehicleValue, IsInInventory);
		return CurrentCatalogVehicle;
	}
	return CurrentCatalogVehicle;
}

void ABaseGarage::DestroyPreviousVehicle()
{
	if (CurrentCatalogVehicle)
	{
		CurrentCatalogVehicle->Destroy();
	}
}

void ABaseGarage::SpawnNewVehicle(int32 VehicleValue, bool IsInInventory)
{
	FVector Location = VehicleStand->GetSocketLocation(FName(TEXT("AttachVehicle")));
	FRotator Rotation = VehicleStand->GetSocketRotation(FName(TEXT("AttachVehicle")));
	FActorSpawnParameters SpawnParameters;
	if (IsInInventory)
	{
		CurrentCatalogVehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(PlayerController->GetInventory()->GetVehicleInventory().Find(VehicleValue)->VehicleClass, Location, Rotation, SpawnParameters);
	}
	else
	{
		CurrentCatalogVehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(VehicleCatalog.Find(VehicleValue)->Get(), Location, Rotation, SpawnParameters);
	}

	CurrentCatalogVehicle->GetMesh()->SetSimulatePhysics(false);
	CurrentCatalogVehicle->AttachToComponent(VehicleStand, FAttachmentTransformRules::KeepRelativeTransform);
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