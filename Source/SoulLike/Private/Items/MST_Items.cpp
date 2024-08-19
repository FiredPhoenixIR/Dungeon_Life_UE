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
}

void AMST_Items::Tick(float DeltaTime) // Seconds/Frame
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
}

float AMST_Items::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AMST_Items::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}