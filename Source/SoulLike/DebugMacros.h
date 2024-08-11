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