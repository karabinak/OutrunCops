#include "StartingRoad.h"

#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "BaseVehiclePawn.h"
#include "Kismet/GameplayStatics.h"


AStartingRoad::AStartingRoad()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	AnimationTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("StartAnimationTrigger"));

	SplineComp->SetupAttachment(GetRootComponent());
	AnimationTrigger->SetupAttachment(GetRootComponent());
}

void AStartingRoad::BeginPlay()
{
	Super::BeginPlay();

	AnimationTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AnimationTrigger->OnComponentBeginOverlap.AddDynamic(this, &AStartingRoad::OnAnimationOverlap);
	AnimationTrigger->OnComponentEndOverlap.AddDynamic(this, &AStartingRoad::OnAnimationEndOverlap);

	GetWorld()->GetTimerManager().SetTimer(TriggerDelay, this, &AStartingRoad::ActiveAnimationBox, 1.f);
}

void AStartingRoad::OnAnimationOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseVehiclePawn* Pawn = Cast<ABaseVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn == OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("BeginOver"));
		Pawn->PathDriving(SplineComp);
	}
} 

void AStartingRoad::OnAnimationEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABaseVehiclePawn* Pawn = Cast<ABaseVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn == OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("EndOver"));
		AnimationTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		Pawn->PathDriving(nullptr);
		Pawn->SetVehicleState(EVehicleState::EVS_Active);
	}
}

void AStartingRoad::ActiveAnimationBox()
{
	AnimationTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
