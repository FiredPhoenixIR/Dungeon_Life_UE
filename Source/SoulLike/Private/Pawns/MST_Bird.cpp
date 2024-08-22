// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MST_Bird.h"
#include "Components/CapsuleComponent.h" 
//Used forward declare in our header and used componenet header file here 
//Where we actually need the size and info to create an object of it
//Prevents code bloat and circular dependencies and reduce compile time
 
// Sets default values
AMST_Bird::AMST_Bird()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(RootComponent);
	//SetRootComponent(Capsule);
}

void AMST_Bird::BeginPlay()
{
	Super::BeginPlay();
}

void AMST_Bird::MoveForward(float Value)
{ // called everyframe like tick as its bound
	UE_LOG(LogTemp, Warning, TEXT("Value : %f "), Value);
	if (Controller && (Value != 0.f)) {
		FVector LForward = GetActorForwardVector();
		AddMovementInput(LForward, Value);
	}
}

void AMST_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMST_Bird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMST_Bird::MoveForward); // Bind To CallBackFuncction
}

