
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "BaseMenuWidget.h"
#include "BaseShopWidget.h"
#include "BaseVehiclePawn.h"
#include "BasePlayerController.h"
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
	CreateShopyWidget();

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

	SetPreviewVehicle(0);
}

void ABaseGarage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGarage::SetPreviewVehicle(int32 CurrentValue)
{
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
	}
}

void ABaseGarage::CreateMenuWidget()
{
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	}
}

void ABaseGarage::CreateShopyWidget()
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