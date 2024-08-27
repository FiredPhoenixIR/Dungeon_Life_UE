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
	else {
		// Debug log if the character is null
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to get EchoCharacter in NativeInitializeAnimation"));
		}
	}
}

void UMST_EchoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (EchoCharacterMovement) {
		GroundSpeed = UKismetMathLibrary::VSizeXY(EchoCharacterMovement->Velocity);
		bSprinting = EchoCharacter->bIsSprinting;
	

	//	if (GEngine) {
	//		FString SpeedText = FString::Printf(TEXT("GroundSpeed: %.2f"), GroundSpeed);
	//		FString SprintingText = FString::Printf(TEXT("bSprinting: %s"), bSprinting ? TEXT("True") : TEXT("False"));
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, SpeedText);
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, SprintingText);
	//	}
	//}
	//else {
	//	// Debug log if the movement component is null
	//	if (GEngine) {
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to get EchoCharacterMovement in NativeUpdateAnimation"));
	//	}
	}
}
