// Copyright NeuroGames


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Game/PlayerControllers/TBSPlayerController.h"
#include "Game/PlayerControllers/TBSPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TBS_Fantasy/TBS_Fantasy.h"
#include "UI/HUD/TBSHUD.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, YawRotationSpeed, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = SpringArmLength;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	const FRotator SpringArmRotation = FRotator(-35.0f, 0.0f, 0.0f);
	SpringArm->AddWorldRotation(SpringArmRotation);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	
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

void APlayerCharacter::SelectPawn()
{
	APlayerController* ThisPlayerController = Cast<APlayerController>(GetController());
	if (!ThisPlayerController) {return;}
	this->ReceivePossessed(ThisPlayerController);
	bIsSelected = true;
	
	// APawn* SelectedPawn = Cast<APawn>(this);
	// ThisPlayerController->SetPawn(this);
	// APlayerCharacter::PossessedBy(ThisPlayerController);
	
	
}

void APlayerCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	Shield->SetRenderCustomDepth(true);
	Shield->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
}

void APlayerCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	Shield->SetRenderCustomDepth(false);
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
