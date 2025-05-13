// Copyright NeuroGames


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Game/PlayerControllers/TBSPlayerController.h"
#include "Game/PlayerControllers/TBSPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/HUD/TBSHUD.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = SpringArmLength;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	
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

void APlayerCharacter::SelectPawn(AController* NewController)
{
	AController* ThisPlayerController = this->GetController();
	if (ThisPlayerController != nullptr && NewController != nullptr)
	{
		if (ThisPlayerController != NewController)
		{
			APlayerCharacter::PossessedBy(NewController);
		}
	}
}

void APlayerCharacter::InitAbilityActorInfo()
{
	
	//TODO: check(TBSPlayerState) -> throws an exception, need to figure out why. Am using if statement instead 

	if (ATBSPlayerState* TBSPlayerState = GetPlayerState<ATBSPlayerState>())
	{
		TBSPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TBSPlayerState, this);
		AbilitySystemComponent = TBSPlayerState->GetAbilitySystemComponent();
		AttributeSet = TBSPlayerState->GetAttributeSet();

		if(ATBSPlayerController* TBSPlayerController = Cast<ATBSPlayerController>(GetController()))
		{
			if(ATBSHUD* TBSHUD = Cast<ATBSHUD>(TBSPlayerController->GetHUD()))
			{
				TBSHUD->InitOverlay(TBSPlayerController, TBSPlayerState, AbilitySystemComponent, AttributeSet);
			}
		}	
	}
	
	
	
	
}
