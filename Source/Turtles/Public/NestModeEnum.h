// Made by Maxim "RenViscoso" Levin for a test task from Fntastic

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ENestMode: uint8
{
	Turtle_Standard UMETA(DisplayName = "Standard"),
	Turtle_WithStops UMETA(DisplayName = "WithStops"),
	Turtle_Reverse UMETA(DisplayName = "Reverse"),
};