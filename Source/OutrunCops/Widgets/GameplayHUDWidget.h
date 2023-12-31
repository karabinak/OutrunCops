

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUDWidget.generated.h"


class AVehiclePawn;

UCLASS()
class OUTRUNCOPS_API UGameplayHUDWidget : public UUserWidget
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
	AVehiclePawn* PawnRef;

};
