// Copyright NeuroGames


#include "Game/PlayerControllers/ExplorationPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Pawn/CameraPawn.h"

AExplorationPlayerController::AExplorationPlayerController()
{
	bReplicates = true;
}

void AExplorationPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind Actions
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
		this, &AExplorationPlayerController::Move);
	EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered,
		this, &AExplorationPlayerController::Rotate);
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered,
		this, &AExplorationPlayerController::Zoom);
	
}

void AExplorationPlayerController::BeginPlay()
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

void AExplorationPlayerController::Move(const FInputActionValue& InputActionValue)
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

void AExplorationPlayerController::Rotate(const FInputActionValue& InputActionValue)
{
	if (!bCanRotate) return;
	
	const float Input = InputActionValue.Get<float>();

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(Input * RotateSpeed);
		ControlledPawn->AddActorWorldRotation(FRotator(0, Input * RotateSpeed, 0));
	}
}

void AExplorationPlayerController::Zoom(const FInputActionValue& InputActionValue)
{
	const float Input = InputActionValue.Get<float>();
	if(ACameraPawn* ControlledPawn = GetPawn<ACameraPawn>())
	{
		ControlledPawn->SetSpringArmLength(FMath::Clamp(Input * ZoomSpeed + ControlledPawn->GetSpringArmLength(),
			MinArmLength, MaxArmLength));
		
	}
	
	
}
