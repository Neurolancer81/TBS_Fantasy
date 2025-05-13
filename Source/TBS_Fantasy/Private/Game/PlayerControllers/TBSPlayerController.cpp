// Copyright NeuroGames


#include "Game/PlayerControllers/TBSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/PawnSelectionInterface.h"
#include "Pawn/CameraPawn.h"

ATBSPlayerController::ATBSPlayerController()
{
	bReplicates = true;
}

void ATBSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind Actions
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
		this, &ATBSPlayerController::Move);
	EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered,
		this, &ATBSPlayerController::Rotate);
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered,
		this, &ATBSPlayerController::Zoom);
	
}

void ATBSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ATBSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if(Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);	
	}	

	// Cursor mode setup
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
}

void ATBSPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y * MoveSpeed);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X * MoveSpeed);
	}
}

void ATBSPlayerController::Rotate(const FInputActionValue& InputActionValue)
{
	if (!bCanRotate) return;
	
	const float Input = InputActionValue.Get<float>();

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(Input * RotateSpeed);
		ControlledPawn->AddActorWorldRotation(FRotator(0, Input * RotateSpeed, 0));
	}
}

void ATBSPlayerController::Zoom(const FInputActionValue& InputActionValue)
{
	const float Input = InputActionValue.Get<float>();
	if(ACameraPawn* ControlledPawn = GetPawn<ACameraPawn>())
	{
		ControlledPawn->SetSpringArmLength(FMath::Clamp(Input * ZoomSpeed + ControlledPawn->GetSpringArmLength(),
			MinArmLength, MaxArmLength));
		
	}
	
	
}

void ATBSPlayerController::Possess(const FInputActionValue& InputActionValue)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit) return;

	LastSelectedActor = ThisSelectedActor;
	ThisSelectedActor = HitResult.GetActor();

	if (ThisSelectedActor != nullptr)
	{
		ThisSelectedActor->SelectPawn(this);
	}
	
}

void ATBSPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastEnemyActor = ThisEnemyActor;
	ThisEnemyActor = CursorHit.GetActor();

	/**
	 * Case A: LastEnemyActor is null and ThisEnemyActor is Null
	 *		-> Do Nothing
	 * Case B: LastEnemyActor is null and ThisEnemyActor is valid
	 *		-> Highlight this actor
	 * Case C: LastEnemyActor is Valid and ThisEnemyActor is null
	 *		-> UnHighlight LastEnemyActor
	 *	Case D: Both Actors are valid but they are not the same
	 *		-> UnHighlight LastEnemyActor and Highlight ThisEnemyActor
	 *	Case E: Both Actors are valid and they are the same
	 *		-> Do Nothing	
	 * **/

	if (LastEnemyActor == nullptr)
	{
		if (ThisEnemyActor == nullptr)
		{
			// Case A: Do Nothing
		}
		else
		{
			// Case B: Highlight this actor
			ThisEnemyActor->HighlightActor();
		}		
	}
	else
	{
		if (ThisEnemyActor == nullptr)
		{
			//Case C: Unhighlight last actor
			LastEnemyActor->UnHighlightActor();
		}
		else
		{
			if (LastEnemyActor != ThisEnemyActor)
			{
				// Case D: UnHighlight LastEnemyActor and Highlight ThisEnemyActor
				LastEnemyActor->UnHighlightActor();
				ThisEnemyActor->HighlightActor();
			}
			else
			{
				// Case E: Do nothing
			}
		}
	}
}
