// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MST_EchoAnimInstance.h"
#include "Characters/MST_EchoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMST_EchoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EchoCharacter = Cast<AMST_EchoCharacter>(TryGetPawnOwner());
	if (EchoCharacter) {
		EchoCharacterMovement = EchoCharacter->GetCharacterMovement();
	}
}

void UMST_EchoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (EchoCharacterMovement) {
		GroundSpeed = UKismetMathLibrary::VSizeXY(EchoCharacterMovement->Velocity);
		bSprinting = EchoCharacter->bIsSprinting;
	}
}


