#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseMenuWidget.generated.h"

class ABaseGarage;

UCLASS()
class OUTRUNCOPS_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	ABaseGarage* GarageRef;


public:

	void SetGarageRef(ABaseGarage* BaseGarage) { GarageRef = BaseGarage; }

};
