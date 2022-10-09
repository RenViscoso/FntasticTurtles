// Made by Maxim "RenViscoso" Levin for a test task from Fntastic

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NestModeEnum.h"
#include "TurtlesWidget.generated.h"


UCLASS(Abstract, Blueprintable, ClassGroup=(Turtles))
class TURTLES_API UTurtlesWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "TurtleFinished"))
	void ReceiveTurtleFinished(ENestMode NestMode);

	
	virtual void TurtleFinished(ENestMode NestMode) PURE_VIRTUAL(UTurtlesWidget::TurtleFinished,);
};
