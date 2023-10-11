
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "BaseMenuWidget.h"
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
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
		Cast<UBaseMenuWidget>(MenuWidget)->SetGarageRef(this);
	}

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTarget(this);
}


void ABaseGarage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGarage::SetPreviewVehicle(int32 CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("%i"), CurrentValue);
}

void ABaseGarage::CreateMenuWidget()
{
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	}
}
