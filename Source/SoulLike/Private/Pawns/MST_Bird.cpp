// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MST_Bird.h"
#include "Components/CapsuleComponent.h" 
//As we used forward declare and dont need size and all info of componenet
//Prevents code bloat and circular dependencies and reduce compile time
 
// Sets default values
AMST_Bird::AMST_Bird()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = Capsule;
	//SetRootComponent(Capsule);
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

