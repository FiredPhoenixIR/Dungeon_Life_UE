#include "Characters/MST_EchoAnimInstance.h"
#include "Characters/MST_EchoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h" // For GEngine->AddOnScreenDebugMessage

void UMST_EchoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Ensure we have a valid pawn
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
