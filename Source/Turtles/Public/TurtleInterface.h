// Made by Maxim "RenViscoso" Levin for a test task from Fntastic

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TurtlesWidget.h"
#include "TurtleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTurtleInterface : public UInterface
{
	GENERATED_BODY()
};


class TURTLES_API ITurtleInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "SetTurtleComponent"))
	void SetTurtleComponent(UTurtlesWidget* InWidget, ENestMode InMode, const FVector InTargetPoint);
};
