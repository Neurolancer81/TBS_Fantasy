// Copyright NeuroGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TBSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TBS_FANTASY_API UTBSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
	
};
