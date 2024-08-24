// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MST_EchoCharacter.generated.h"


UCLASS()
class SOULLIKE_API AMST_EchoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMST_EchoCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
};
