#pragma once

#include "DrawDebugHelpers.h"

#define DebugSphere(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 30.f, 15, FColor::Emerald, true);
#define DebugLine(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
#define DebugPoint(PointLocation) if (GetWorld()) DrawDebugPoint(GetWorld(), PointLocation, 20.f,FColor::Magenta, true, 01.f, 0);
#define DebugVector(StartLoc, EndLoc) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLoc, 20.f, FColor::Magenta, true, 01.f, 0); \
	};

#define DebugSphere_SingleFrame(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 8, FColor::Red, false, -1.f);
#define DebugLine_SingleFrame(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
#define DebugPoint_SingleFrame(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, false, -1.f);
#define DebugVector_SingleFrame(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, false, -1.f); \
	}

// Some Tests:
//void AMST_Items::BeginPlay()
//{
//	Super::BeginPlay();
//	UE_LOG(LogTemp, Warning, TEXT("BeginPlay Called ! ")); //SemiCol Optional as UE LOG is a macro
//	if (GEngine) {
//		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Yellow, FString(" Item Message "));
//	}
//
//	//FVector Location = GetActorLocation();
//	//FVector Forward = GetActorForwardVector();
//	SetActorLocation(FVector(0.f, 0.f, 120.f));
//	//DebugSphere(Location);
//	//DebugVector(Location, Location + Forward * 100);
//}
//
//void AMST_Items::Tick(float DeltaTime) // Seconds/Frame
//{
//	Super::Tick(DeltaTime);
//	UE_LOG(LogTemp, Warning, TEXT("DeltaTime : %f"), DeltaTime);
//
//	if (GEngine) {
//		FString Name = GetName();
//		//FString Message = FString::Printf(TEXT("Delta Time : %f"), DeltaTime);
//		FString Message = FString::Printf(TEXT("Object Name : %s"), *Name);
//		// * overloaded for fstring var , provides c style string ( an array of char)
//		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, Message);
//	}
//	float Time = GetWorld()->GetTimeSeconds();
//	SetActorLocation(FVector(50.f + 10 * Time, 0.f, 300.f + 50.f * sin(Time)));
//	//AddActorWorldRotation(FRotator(5.0f * DeltaTime, 5.f * DeltaTime, 5.f * DeltaTime)); // Testing Gimble Lock
//	//AddActorWorldRotation(FQuat(FRotator(5.0f * DeltaTime, 5.f * DeltaTime, 5.f * DeltaTime)));
//
//
//
//	// Separate rotation values
//	float PitchRotation = 15.0f * DeltaTime;
//	float YawRotation = 15.0f * DeltaTime;
//	float RollRotation = 15.0f * DeltaTime;
//
//	// Get the current rotation as a quaternion
//	FQuat CurrentRotation = GetActorQuat();
//
//	// Create individual quaternions for each axis
//	FQuat QuatPitch = FQuat(FRotator(PitchRotation, 0.f, 0.f));
//	FQuat QuatYaw = FQuat(FRotator(0.f, YawRotation, 0.f));
//	FQuat QuatRoll = FQuat(FRotator(0.f, 0.f, RollRotation));
//
//	// Combine the rotations
//	FQuat NewRotation = QuatPitch * QuatYaw * QuatRoll;
//
//	// Apply the combined rotation
//	SetActorRotation(CurrentRotation * NewRotation);
//	DebugSphere_SingleFrame(GetActorLocation());
//	DebugVector_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100);
//}