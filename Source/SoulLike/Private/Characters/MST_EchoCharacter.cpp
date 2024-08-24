// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MST_EchoCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"

// Sets default values
AMST_EchoCharacter::AMST_EchoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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
	
}

void AMST_EchoCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0) {
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMST_EchoCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0) {
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMST_EchoCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMST_EchoCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMST_EchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMST_EchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMST_EchoCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AMST_EchoCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AMST_EchoCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AMST_EchoCharacter::LookUp);
}

