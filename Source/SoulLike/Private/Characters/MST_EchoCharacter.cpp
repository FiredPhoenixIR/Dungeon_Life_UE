// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MST_EchoCharacter.h"

// Sets default values
AMST_EchoCharacter::AMST_EchoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMST_EchoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMST_EchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMST_EchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

