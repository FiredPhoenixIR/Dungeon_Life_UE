// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MST_Bird.generated.h"

class UCapsuleComponent;

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

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;
};
