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

USTRUCT()
struct FSnapshot
{
	GENERATED_BODY()

	FVector PlayerPosition;
	FVector PlayerVelocity;
	float TimeStamp;

	FSnapshot() {}
	FSnapshot(FVector Position, FVector Velocity, float Time)
		: PlayerPosition(Position), PlayerVelocity(Velocity), TimeStamp(Time)
	{}
};


UCLASS()
class SOULLIKE_API AMST_EchoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMST_EchoCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_bIsSprinting)
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsJumping;

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

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EKeyAction;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//bool bIsSprinting;
	virtual void Jump() override;
	void Attack();
	void Dodge();
	void EKeyPressed();
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

	UPROPERTY(VisibleAnywhere, Replicated)
	float WalkSpeed;
	UPROPERTY(VisibleAnywhere, Replicated)
	float SprintSpeed;



private:
	void RecordSnapshot();
	FSnapshot FindClosestSnapshot(float TargetTime) const;
	//Snapshots
	TArray<FSnapshot> SnapshotHistory;
	float SnapshotInterval = 0.05f; // Record a snapshot every 50ms
	float MaxHistoryTime = 1.0f;    // Keep 1 second of history

	// Variables for movement prediction
	UPROPERTY(Replicated)
	FVector ServerPosition;

	UPROPERTY(Replicated)
	FVector LastProcessedPosition;

public:

	// Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	// Network functions
	UFUNCTION(Server, Unreliable)
	void ServerMoveCustom(const FVector2D& MovementVector);

	UFUNCTION(Server, Unreliable)
	void ServerSprint(bool bSprinting);

	UFUNCTION(Server, Unreliable)
	void ServerSetSprintState(bool bShouldSprint);

	// State replication
	UFUNCTION()
	void OnRep_ServerPosition();

	UFUNCTION()
	void OnRep_bIsSprinting();
};
