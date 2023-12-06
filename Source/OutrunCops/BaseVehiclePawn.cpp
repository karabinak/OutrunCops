#include "BaseVehiclePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "MySaveGame.h"
#include "BaseGameInstance.h"

#include "OutrunCopsGameModeGameplay.h"
#include "Kismet/GameplayStatics.h"

ABaseVehiclePawn::ABaseVehiclePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SetRootComponent(GetMesh());
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetSimulatePhysics(true);
	SpringArm->TargetArmLength = 1500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	VehicleWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("VehicleWidget"));
	VehicleWidget->SetupAttachment(GetRootComponent());
	VehicleWidget->SetWidgetSpace(EWidgetSpace::Screen);
	VehicleWidget->SetDrawSize(FVector2D(200.f, 50.f));
	VehicleWidget->SetPivot(FVector2D(0.f, 1.f));


	// CAR PARTS
	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_Wheel"));
	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_Wheel"));
	WheelRL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RL_Wheel"));
	WheelRR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RR_Wheel"));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumper"));
	MirrorR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorR"));
	MirrorL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorL"));
	Hood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hood"));
	Trunk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trunk"));

	WheelFL->SetupAttachment(GetMesh(), TEXT("FL"));
	WheelFR->SetupAttachment(GetMesh(), TEXT("FR"));
	WheelRL->SetupAttachment(GetMesh(), TEXT("RL"));
	WheelRR->SetupAttachment(GetMesh(), TEXT("RR"));

	FrontBumper->SetupAttachment(GetMesh());
	RearBumper->SetupAttachment(GetMesh());
	MirrorR->SetupAttachment(GetMesh());
	MirrorL->SetupAttachment(GetMesh());
	Hood->SetupAttachment(GetMesh());
	Trunk->SetupAttachment(GetMesh());

}

void ABaseVehiclePawn::BeginPlay()
{
	Super::BeginPlay();


	GetMesh()->OnComponentHit.AddDynamic(this, &ABaseVehiclePawn::OnHit);

	if (FrontBumper)
	{
		PartsToDetach.Add(FrontBumper);
	}
	if (RearBumper)
	{
		PartsToDetach.Add(RearBumper);
	}
	if (MirrorR)
	{
		PartsToDetach.Add(MirrorR);
	}
	if (MirrorL)
	{
		PartsToDetach.Add(MirrorL);
	}
	if (Hood)
	{
		PartsToDetach.Add(Hood);
	}
	if (Trunk)
	{
		PartsToDetach.Add(Trunk);
	}

	UMySaveGame* DataToLoad = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
	if (DataToLoad != nullptr)
	{
		UBaseGameInstance* Instance = Cast<UBaseGameInstance>(GetGameInstance());

		if (DataToLoad->Inventory.Contains(Instance->GetVehicleInt_Inst()))
		{
			GetMesh()->SetMaterial(0, DataToLoad->Inventory.Find(Instance->GetVehicleInt_Inst())->VehicleCustomization.BodyPaint);

			for (int i = 0; i < PartsToDetach.Num(); i++)
			{
				if (PartsToDetach[i])
				{
					PartsToDetach[i]->SetMaterial(0, DataToLoad->Inventory.Find(Instance->GetVehicleInt_Inst())->VehicleCustomization.BodyPaint);
				}
			}
		}

		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Game Loaded")));
	}

}

void ABaseVehiclePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CalculateDistance();
}

void ABaseVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Throttle", this, &ABaseVehiclePawn::Throttle);
	PlayerInputComponent->BindAxis("Brake", this, &ABaseVehiclePawn::Brake);
	PlayerInputComponent->BindAxis("Steer", this, &ABaseVehiclePawn::Steer);

	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &ABaseVehiclePawn::Interaction);
}

void ABaseVehiclePawn::Throttle(float AxisValue)
{
	GetVehicleMovement()->SetThrottleInput(AxisValue);
}

void ABaseVehiclePawn::Brake(float AxisValue)
{
	GetVehicleMovement()->SetBrakeInput(AxisValue);
}

void ABaseVehiclePawn::Steer(float AxisValue)
{
	GetVehicleMovement()->SetSteeringInput(AxisValue);
}

void ABaseVehiclePawn::CalculateDistance()
{
	if (!bCanCalculateDistance) return;
	const FVector CurrentLocation = GetActorLocation();
	double DistanceOneSec = FVector::Dist(CurrentLocation, LastFrameVector);

	Distance += DistanceOneSec / 100;
	LastFrameVector = CurrentLocation;
}

void ABaseVehiclePawn::ChangeCamera(float Axis)
{
	FRotator NewCameraRot = SpringArm->GetRelativeRotation() + FRotator(0.f, Axis, 0.f);
	SpringArm->SetRelativeRotation(NewCameraRot);
}

void ABaseVehiclePawn::DetachComponent(UStaticMeshComponent* CarPart)
{
	CarPart->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CarPart->SetSimulatePhysics(true);
	CarPart->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	CarPart->AddImpulse(FVector(0.f, 0.f, 500.f));
}

void ABaseVehiclePawn::AttachComponent(UStaticMeshComponent* CarPart)
{
	CarPart->SetSimulatePhysics(false);
	CarPart->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CarPart->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	CarPart->SetWorldRotation(FRotator::ZeroRotator);
	CarPart->SetRelativeLocation(FVector::ZeroVector);
}

void ABaseVehiclePawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bCanHit) return;
	bCanHit = false;

	float Impact = FMath::Floor(NormalImpulse.Length() / 60000.f);
	HitPoints -= Impact;

	if (HitPoints < ActiveParts * OnePartHitPoints && !PartsToDetach.IsEmpty())
	{
		int32 Random = FMath::RandRange(0, PartsToDetach.Num() - 1);
		DetachComponent(PartsToDetach[Random]);
		PartsToDetach.RemoveAt(Random);
	}

	if (HitPoints <= 0.f)
	{
		DetachComponent(WheelFL);
		DetachComponent(WheelFR);
		DetachComponent(WheelRL);
		DetachComponent(WheelRR);


		UChaosWheeledVehicleMovementComponent* EngineRef = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

		EngineRef->WheelSetups[0].WheelClass = nullptr;
		EngineRef->WheelSetups[1].WheelClass = nullptr;
		EngineRef->WheelSetups[2].WheelClass = nullptr;
		EngineRef->WheelSetups[3].WheelClass = nullptr;

	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), HitPoints);
	GetWorld()->GetTimerManager().SetTimer(HitCooldownTimer, this, &ABaseVehiclePawn::ResetCanHit, 3.f);
}

void ABaseVehiclePawn::ResetCanHit()
{
	bCanHit = true;
}

void ABaseVehiclePawn::Interaction()
{

	AOutrunCopsGameModeGameplay* Gamemode = Cast<AOutrunCopsGameModeGameplay>(UGameplayStatics::GetGameMode(GetWorld()));
	Gamemode->EndRun();

}