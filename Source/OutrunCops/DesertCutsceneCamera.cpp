#include "DesertCutsceneCamera.h"

#include "Camera/CameraComponent.h"
#include "BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BaseVehiclePawn.h"

ADesertCutsceneCamera::ADesertCutsceneCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CutsceneCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CineCameraComp"));

	SetRootComponent(CutsceneCamera);
	CutsceneCamera->SetRelativeRotation(CameraBaseRotation);


}

void ADesertCutsceneCamera::BeginPlay()
{
	Super::BeginPlay();
	
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->SetViewTarget(this);
	}

	GetWorld()->GetTimerManager().SetTimer(CameraChangeTime, this, &ADesertCutsceneCamera::ChangeCamera, 4.f);
}

void ADesertCutsceneCamera::ChangeCamera()
{
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ABaseVehiclePawn* Pawn = Cast<ABaseVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn && PlayerController)
	{
		PlayerController->SetViewTarget(Pawn);
	}
}


void ADesertCutsceneCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABaseVehiclePawn* Pawn = Cast<ABaseVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn)
	{
		FVector Location = FMath::VInterpTo(GetActorLocation(), FVector(13000.f, 0.f, Pawn->GetCamera()->GetComponentLocation().Z), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0.5f);
		CutsceneCamera->SetWorldLocation(Location);
	}
}

