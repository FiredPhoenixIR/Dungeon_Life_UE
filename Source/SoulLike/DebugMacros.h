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


//Server Rewinding sample
//void AMyWeapon::ServerFire_Implementation(APlayerController * PlayerController, FVector ShotOrigin, FVector ShotDirection)
//{
//    // Step 1: Calculate the client's ping from PlayerState
//    float ClientPing = PlayerController->PlayerState->GetPing() * 0.001f; // Convert to seconds
//
//    // Step 2: Calculate the time when the shot was fired on the client
//    float FireTime = GetWorld()->GetTimeSeconds() - ClientPing;
//
//    // Step 3: Find the closest snapshot corresponding to the time when the shot was fired
//    AMyCharacter* TargetCharacter = Cast<AMyCharacter>(GetCharacter()); // Assuming this weapon is attached to a character
//    FSnapshot* ClosestSnapshot = TargetCharacter ? TargetCharacter->FindClosestSnapshot(FireTime) : nullptr;
//
//    if (ClosestSnapshot)
//    {
//        // Step 4: Rewind the target character's position to the snapshot position
//        FVector RewindedPosition = ClosestSnapshot->PlayerPosition;
//
//        // Step 5: Perform hit detection using the rewinded position
//        bool bHitDetected = HitDetected(RewindedPosition, ShotOrigin, ShotDirection);
//
//        if (bHitDetected)
//        {
//            // Step 6: Apply damage or other effects
//            UGameplayStatics::ApplyDamage(TargetCharacter, DamageAmount, PlayerController, this, UDamageType::StaticClass());
//        }
//    }
//}
//
//bool AMyWeapon::HitDetected(FVector RewindedPosition, FVector ShotOrigin, FVector ShotDirection)
//{
//    FVector EndLocation = ShotOrigin + (ShotDirection * 10000.0f); // Long range for hit detection
//    FHitResult HitResult;
//
//    // Perform a line trace (raycast) in the world to see if the shot hits the rewinded position
//    bool bHit = GetWorld()->LineTraceSingleByChannel(
//        HitResult,
//        ShotOrigin,
//        EndLocation,
//        ECC_Visibility // Assuming visibility channel for hit detection
//    );
//
//    if (bHit)
//    {
//        // If the hit result's location is close to the rewinded position, consider it a hit
//        float HitDistance = FVector::Dist(HitResult.Location, RewindedPosition);
//        if (HitDistance <= 50.0f) // 50 units tolerance
//        {
//            return true;
//        }
//    }
//
//    return false;
//}


//Ping Client from server
// In your player controller class (e.g., AMyPlayerController)

//UCLASS()
//class YOURGAME_API AMyPlayerController : public APlayerController
//{
//    GENERATED_BODY()
//
//public:
//    // This function will be called periodically by the server to ping the client
//    UFUNCTION(Server, Reliable, WithValidation)
//    void ServerSendPing(int32 PingID);
//
//    // This function will be called by the client to respond to the ping
//    UFUNCTION(Client, Reliable)
//    void ClientRespondPing(int32 PingID, float ServerTime);
//
//private:
//    FTimerHandle PingTimerHandle;
//    TMap<int32, float> PingMap; // Stores ping IDs and their send times
//    int32 CurrentPingID;
//private:
//    float PingTimeout = 2.0f; // 2 seconds timeout for ping response
//
//    void HandlePingTimeout(int32 PingID);
//
//protected:
//    virtual void BeginPlay() override;
//
//    // Function to initiate ping from server
//    void SendPingToClient();
//};
//
//void AMyPlayerController::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // Start sending pings to the client every 2 seconds
//    if (IsLocalController())
//    {
//        return;
//    }
//
//    GetWorldTimerManager().SetTimer(PingTimerHandle, this, &AMyPlayerController::SendPingToClient, 2.0f, true);
//}
//
//void AMyPlayerController::SendPingToClient()
//{
//    CurrentPingID++;
//    float CurrentTime = GetWorld()->GetTimeSeconds();
//    PingMap.Add(CurrentPingID, CurrentTime);
//
//    // Set a timeout to handle cases where the client is out of reach
//    FTimerDelegate TimerDel;
//    TimerDel.BindUFunction(this, FName("HandlePingTimeout"), CurrentPingID);
//    GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDel, PingTimeout);
//
//    ServerSendPing(CurrentPingID);
//}
//
//void AMyPlayerController::ServerSendPing_Implementation(int32 PingID)
//{
//    // Send ping to the client with the current server time
//    ClientRespondPing(PingID, GetWorld()->GetTimeSeconds());
//}
//
//bool AMyPlayerController::ServerSendPing_Validate(int32 PingID)
//{
//    return true;
//}
//
//void AMyPlayerController::ClientRespondPing_Implementation(int32 PingID, float ServerTime)
//{
//    if (IsLocalController())
//    {
//        return;
//    }
//
//    // Send the ping response back to the server
//    ServerSendPing(PingID);
//}
//void AMyPlayerController::HandlePingTimeout(int32 PingID)
//{
//    if (PingMap.Contains(PingID))
//    {
//        // The ping has not been responded to within the timeout period
//        PingMap.Remove(PingID);
//
//        // Optionally log or take action, like marking the client as having network issues
//        UE_LOG(LogTemp, Warning, TEXT("Ping %d timed out."), PingID);
//    }
//}
//
//// ping smooth float SmoothedPing = (PreviousSmoothedPing * 0.8f) + (CurrentPing * 0.2f);
