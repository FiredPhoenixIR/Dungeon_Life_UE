// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/MST_Items.h"
#include "DrawDebugHelpers.h"
#include "SoulLike/DebugMacros.h"



// Sets default values
AMST_Items::AMST_Items()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMST_Items::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay Called ! ")); //SemiCol Optional as UE LOG is a macro
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Yellow, FString(" Item Message "));
	}
	
	//FVector Location = GetActorLocation();
	//FVector Forward = GetActorForwardVector();
	SetActorLocation(FVector(0.f, 0.f, 120.f));
	//DebugSphere(Location);
	//DebugVector(Location, Location + Forward * 100);
}

void AMST_Items::Tick(float DeltaTime) // Seconds/Frame
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("DeltaTime : %f"), DeltaTime);

	if (GEngine) {
		FString Name = GetName();
		//FString Message = FString::Printf(TEXT("Delta Time : %f"), DeltaTime);
		FString Message = FString::Printf(TEXT("Object Name : %s"), *Name); 
		// * overloaded for fstring var , provides c style string ( an array of char)
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, Message);
	}
	float Time = GetWorld()->GetTimeSeconds();
	SetActorLocation(FVector(50.f + 10* Time, 0.f, 300.f + 50.f * sin(Time)));
	//AddActorWorldRotation(FRotator(5.0f * DeltaTime, 5.f * DeltaTime, 5.f * DeltaTime)); // Testing Gimble Lock
	//AddActorWorldRotation(FQuat(FRotator(5.0f * DeltaTime, 5.f * DeltaTime, 5.f * DeltaTime)));



	// Separate rotation values
	float PitchRotation = 15.0f * DeltaTime;
	float YawRotation = 15.0f * DeltaTime;
	float RollRotation = 15.0f * DeltaTime;

	// Get the current rotation as a quaternion
	FQuat CurrentRotation = GetActorQuat();

	// Create individual quaternions for each axis
	FQuat QuatPitch = FQuat(FRotator(PitchRotation, 0.f, 0.f));
	FQuat QuatYaw = FQuat(FRotator(0.f, YawRotation, 0.f));
	FQuat QuatRoll = FQuat(FRotator(0.f, 0.f, RollRotation));

	// Combine the rotations
	FQuat NewRotation = QuatPitch * QuatYaw * QuatRoll;

	// Apply the combined rotation
	SetActorRotation(CurrentRotation * NewRotation);
	DebugSphere_SingleFrame(GetActorLocation());
	DebugVector_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100);
}