

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseGameplayWidget.generated.h"


class ABaseVehiclePawn;

UCLASS()
class OUTRUNCOPS_API UBaseGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CustomConstruct();


public:
	UFUNCTION(BlueprintCallable)
	void AddPauseToViewport();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Properties", meta = (AllowPrivateAccess = "true"))
	ABaseVehiclePawn* PawnRef;

};
