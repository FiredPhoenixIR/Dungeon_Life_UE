// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MST_EchoCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class SOULLIKE_API AMST_EchoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMST_EchoCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsSprinting;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* EchoContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookingAction;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//bool bIsSprinting;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Groom")
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = "Groom")
	UGroomComponent* EyeBrows;

	UPROPERTY(VisibleAnywhere)
	float WalkSpeed;
	UPROPERTY(VisibleAnywhere)
	float SprintSpeed;
};
