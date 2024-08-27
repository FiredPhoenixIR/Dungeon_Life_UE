// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MST_EchoCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AMST_EchoCharacter::AMST_EchoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	WalkSpeed = 300.f;
	SprintSpeed = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->SetIsReplicated(true);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); // Yaw is rotation against Z

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	EyeBrows = CreateDefaultSubobject<UGroomComponent>(TEXT("EyeBrows"));
	EyeBrows->SetupAttachment(GetMesh());
	EyeBrows->AttachmentName = FString("head");

}

void AMST_EchoCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {

			Subsystem->AddMappingContext(EchoContext, 0);
		}
	}
	
}

void AMST_EchoCharacter::Move(const FInputActionValue& Value)
{
	//if (ActionState != EActionState::EAS_Unoccupied) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (HasAuthority())
	{
		// Server-side movement processing
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Forward, MovementVector.Y);
		AddMovementInput(Right, MovementVector.X);

		// Update authoritative position
		ServerPosition = GetActorLocation();
	}
	else
	{
		// Predict movement locally on the client
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Forward, MovementVector.Y);
		AddMovementInput(Right, MovementVector.X);

		// Send input to server for validation
		ServerMoveCustom(MovementVector);
	}
}

void AMST_EchoCharacter::ServerMoveCustom_Implementation(const FVector2D& MovementVector)
{
	if (HasAuthority())
	{
		// Server-side validation and processing
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Forward, MovementVector.Y);
		AddMovementInput(Right, MovementVector.X);

		// Update authoritative position
		ServerPosition = GetActorLocation();
	}
}

void AMST_EchoCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate ServerPosition if necessary
	DOREPLIFETIME(AMST_EchoCharacter, ServerPosition);
	DOREPLIFETIME(AMST_EchoCharacter, LastProcessedPosition);
	DOREPLIFETIME(AMST_EchoCharacter, bIsSprinting);
}

void AMST_EchoCharacter::OnRep_ServerPosition()
{
	// Smoothly reconcile the client’s position with the server's position
	FVector Delta = ServerPosition - GetActorLocation();
	if (Delta.SizeSquared() > SMALL_NUMBER)
	{
		FVector NewLocation = FMath::VInterpTo(GetActorLocation(), ServerPosition, GetWorld()->GetDeltaSeconds(), 10.0f);
		SetActorLocation(NewLocation);
	}
}

void AMST_EchoCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

void AMST_EchoCharacter::Sprint(const FInputActionValue& Value)
{
	// Ensure this logic runs only on the server
	if (HasAuthority())
	{
		bool bShouldSprint = Value.Get<bool>();
		if (bShouldSprint) {
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
			bIsSprinting = true;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
			bIsSprinting = false;
		}

		// Notify clients
		OnRep_bIsSprinting();
	}
	else
	{
		// If this is a client, call the server to set the sprint state
		ServerSetSprintState(Value.Get<bool>());
	}
}

void AMST_EchoCharacter::ServerSetSprintState_Implementation(bool bShouldSprint)
{
	Sprint(FInputActionValue(bShouldSprint));  // Call the Sprint function on the server
}

void AMST_EchoCharacter::OnRep_bIsSprinting()
{
	// Update the character movement based on the replicated sprinting state
	GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}

void AMST_EchoCharacter::ServerSprint_Implementation(bool Sprinting)
{
	// Change MaxWalkSpeed on the server
	if (Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	bIsSprinting = Sprinting;
}

void AMST_EchoCharacter::Jump()
{
	Super::Jump();
	bIsJumping = true;
}

void AMST_EchoCharacter::Attack()
{
	return;
}

void AMST_EchoCharacter::Dodge()
{
	return;
}

void AMST_EchoCharacter::EKeyPressed()
{
	return;
}

void AMST_EchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (SnapshotHistory.Num() > 0) // Ensure there's at least one element in the array
	{
		// Check if it's time to record a new snapshot
		if (GetWorld()->GetTimeSeconds() - SnapshotHistory.Last().TimeStamp > SnapshotInterval)
		{
			RecordSnapshot();
		}

		// Remove old snapshots
		while (SnapshotHistory.Num() > 0 && GetWorld()->GetTimeSeconds() - SnapshotHistory[0].TimeStamp > MaxHistoryTime)
		{
			SnapshotHistory.RemoveAt(0);
		}
	}
}

void AMST_EchoCharacter::RecordSnapshot()
{
	FVector CurrentPosition = GetActorLocation();
	FVector CurrentVelocity = GetVelocity();
	float CurrentTime = GetWorld()->GetTimeSeconds();

	FSnapshot NewSnapshot(CurrentPosition, CurrentVelocity, CurrentTime);
	SnapshotHistory.Add(NewSnapshot);
}

FSnapshot AMST_EchoCharacter::FindClosestSnapshot(float TargetTime) const
{
	FSnapshot ClosestSnapshot;
	float ClosestTimeDiff = FLT_MAX; // Initialize with a large value

	for (const FSnapshot& Snapshot : SnapshotHistory)
	{
		float TimeDiff = FMath::Abs(Snapshot.TimeStamp - TargetTime);
		if (TimeDiff < ClosestTimeDiff)
		{
			ClosestTimeDiff = TimeDiff;
			ClosestSnapshot = Snapshot;
		}
	}

	// Return a default snapshot if none is found
	return ClosestTimeDiff == FLT_MAX ? FSnapshot() : ClosestSnapshot;
}

// Called to bind functionality to input
void AMST_EchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Move & Look
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::Move);
		EnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::Look);
		// Bind Sprint Actions
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMST_EchoCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMST_EchoCharacter::Sprint);
		//Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::Jump);
		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::Attack);
		//Dodge
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::Dodge);
		//Equip Interact
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::EKeyPressed);
	}
	//PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMST_EchoCharacter::MoveForward);
}



//void AMST_EchoCharacter::MoveForward(float Value)
//{
//	if (Controller && Value != 0) {
//		const FRotator ControlRotation = GetControlRotation();
//		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
//		
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//		AddMovementInput(Direction, Value);
//	}
//}
//
//void AMST_EchoCharacter::MoveRight(float Value)
//{
//	if (Controller && Value != 0) {
//		const FRotator ControlRotation = GetControlRotation();
//		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
//
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//		AddMovementInput(Direction, Value);
//	}
//}

//void AMST_EchoCharacter::Turn(float Value)
//{
//	AddControllerYawInput(Value);
//}
//
//void AMST_EchoCharacter::LookUp(float Value)
//{
//	AddControllerPitchInput(Value);
//}
