// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MST_Bird.generated.h"

class UCapsuleComponent;
//class USkeletalMeshComponent; already part of pawn and actor
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SOULLIKE_API AMST_Bird : public APawn
{
	GENERATED_BODY()

public:
	AMST_Bird();
	virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);
private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
};
