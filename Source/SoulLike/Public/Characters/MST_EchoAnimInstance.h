// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MST_EchoAnimInstance.generated.h"

class AMST_EchoCharacter;
class UCharacterMovementComponent;

/**
 Careful with null pointers as this is updating everty tick even when game is not running
 **/
UCLASS()
class SOULLIKE_API UMST_EchoAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly) // Exposed to event graph
	AMST_EchoCharacter* EchoCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	UCharacterMovementComponent* EchoCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bSprinting;

};
