#include "CutsceneCameraDesert.h"

// Engine
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Custom
#include "OutrunCops/Cutscenes/CutsceneCameraDesert.h"
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/Controllers/MyPlayerController.h"

//////////////////////////////////////////////////////

ACutsceneCameraDesert::ACutsceneCameraDesert()
{
	PrimaryActorTick.bCanEverTick = true;

	CutsceneCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CineCameraComp"));

	SetRootComponent(CutsceneCamera);
	CutsceneCamera->SetRelativeRotation(CameraBaseRotation);

}

void ACutsceneCameraDesert::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerPawn = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PC)
	{
		PC->SetViewTarget(this);
	}

	GetWorld()->GetTimerManager().SetTimer(CameraChangeTime, this, &ACutsceneCameraDesert::ChangeCamera, 4.f);
}

void ACutsceneCameraDesert::ChangeCamera()
{

	if (PlayerPawn && PC)
	{
		PC->SetViewTarget(PlayerPawn);
	}
}


void ACutsceneCameraDesert::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn)
	{
		FVector Location = FMath::VInterpTo(GetActorLocation(), FVector(13000.f, 0.f, PlayerPawn->GetCamera()->GetComponentLocation().Z), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0.5f);
		CutsceneCamera->SetWorldLocation(Location);
	}
}

