// Copyright NeuroGames


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Game/PlayerControllers/TBSPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for the server
	InitAbilityActorInfo();
	
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for the client
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
		
	if (ATBSPlayerState* TBSPlayerState = GetPlayerState<ATBSPlayerState>())
	{
		TBSPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TBSPlayerState, this);
		AbilitySystemComponent = TBSPlayerState->GetAbilitySystemComponent();
		AttributeSet = TBSPlayerState->GetAttributeSet();	
	}
	
}
