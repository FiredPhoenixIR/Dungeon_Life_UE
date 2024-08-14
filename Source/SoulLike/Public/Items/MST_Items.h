// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MST_Items.generated.h"

UCLASS()
class SOULLIKE_API AMST_Items : public AActor
{
	GENERATED_BODY()
	
public:	

	AMST_Items();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	template<typename T>
	T Avg(T Numb1, T Numb2);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	float amplitude;
};

template<typename T>
inline T AMST_Items::Avg(T Numb1, T Numb2)
{
	return (Numb1 + Numb2) / 2;
}
