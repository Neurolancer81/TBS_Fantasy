// Copyright NeuroGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TBSHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UTBSUserWidget;
/**
 * 
 */
UCLASS()
class TBS_FANTASY_API ATBSHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UTBSUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	void InitOverlay(APlayerController* PlayerController,
		APlayerState* PlayerState,
		UAbilitySystemComponent* AbilitySystemComponent,
		UAttributeSet* AttributeSet);

protected:


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTBSUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	
};
