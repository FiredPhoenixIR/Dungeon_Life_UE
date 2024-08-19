// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MST_Bird.h"

// Sets default values
AMST_Bird::AMST_Bird()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMST_Bird::BeginPlay()
{
	Super::BeginPlay();
}

void AMST_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMST_Bird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

