// Copyright NeuroGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TBSPlayerController.generated.h"

class IPawnSelectionInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;


/**
 * 
 */
UCLASS()
class TBS_FANTASY_API ATBSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATBSPlayerController();
	virtual void SetupInputComponent() override;
	
	

protected:	
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> RotateAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> PossessAction;

	UPROPERTY(EditAnywhere, Category = Input)
	bool bCanRotate = true;
	
	UPROPERTY(EditAnywhere, Category = Input)
	float ZoomSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = Input)
	float MinArmLength = 200.0f;
	UPROPERTY(EditAnywhere, Category = Input)
	float MaxArmLength = 2000.0f;

	UPROPERTY(EditAnywhere, Category = Input)
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, Category = Input)
	float RotateSpeed = 25.0f;

	void Move(const FInputActionValue& InputActionValue);
	void Rotate(const FInputActionValue& InputActionValue);
	void Zoom(const FInputActionValue& InputActionValue);
	void Possess(const FInputActionValue& InputActionValue);
	
	void CursorTrace();
	void SetSelectedPawn();

	TScriptInterface<IEnemyInterface> LastEnemyActor;
	TScriptInterface<IEnemyInterface> ThisEnemyActor;

	TScriptInterface<IPawnSelectionInterface> LastSelectedActor;
	TScriptInterface<IPawnSelectionInterface> ThisSelectedActor;
	
};
