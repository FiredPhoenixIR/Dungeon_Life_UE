// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define DebugSphere(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 30.f, 15, FColor::Emerald, true);

