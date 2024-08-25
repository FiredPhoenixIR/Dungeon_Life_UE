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



// Sets default values
AMST_EchoCharacter::AMST_EchoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WalkSpeed = 300.f;
	SprintSpeed = 600.f;

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

	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Forward, MovementVector.Y);
	AddMovementInput(Right, MovementVector.X);

}

void AMST_EchoCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

void AMST_EchoCharacter::Sprint(const FInputActionValue& Value)
{
	if (Value.Get<bool>()) {
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		bIsSprinting = true;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		bIsSprinting = false;
	}
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

void AMST_EchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMST_EchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::Move);
		EnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &AMST_EchoCharacter::Look);
		// Bind Sprint Actions
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMST_EchoCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMST_EchoCharacter::Sprint);
	}
	//PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMST_EchoCharacter::MoveForward);
}

