// Copyright NeuroGames


#include "Game/PlayerControllers/TBSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Interaction/EnemyInterface.h"
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

	check(Subsystem);

	Subsystem->AddMappingContext(InputMappingContext, 0);

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

void ATBSPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 * Case A: LastActor is null and ThisActor is Null
	 *		-> Do Nothing
	 * Case B: LastActor is null and ThisActor is valid
	 *		-> Highlight this actor
	 * Case C: LastActor is Valid and ThisActor is null
	 *		-> UnHighlight LastActor
	 *	Case D: Both Actors are valid but they are not the same
	 *		-> UnHighlight LastActor and Highlight ThisActor
	 *	Case E: Both Actors are valid and they are the same
	 *		-> Do Nothing	
	 * **/

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			// Case A: Do Nothing
		}
		else
		{
			// Case B: Highlight this actor
			ThisActor->HighlightActor();
		}		
	}
	else
	{
		if (ThisActor == nullptr)
		{
			//Case C: Unhighlight last actor
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				// Case D: UnHighlight LastActor and Highlight ThisActor
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E: Do nothing
			}
		}
	}
}
