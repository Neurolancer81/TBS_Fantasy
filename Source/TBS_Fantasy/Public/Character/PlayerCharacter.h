// Copyright NeuroGames

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/PawnSelectionInterface.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class TBS_FANTASY_API APlayerCharacter : public ACharacterBase, public IPawnSelectionInterface
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SelectPawn() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
private:
	void InitAbilityActorInfo();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float SpringArmLength = 1000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY()
	bool bIsSelected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float YawRotationSpeed = 200.0f;
	
	
};
