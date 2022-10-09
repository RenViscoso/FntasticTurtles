// Made by Maxim "RenViscoso" Levin for a test task from Fntastic

#pragma once

#include "CoreMinimal.h"
#include "NestModeEnum.h"
#include "TurtlesWidget.h"
#include "GameFramework/MovementComponent.h"
#include "TurtleComponent.generated.h"


USTRUCT(BlueprintType)
struct FTimeSet
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float StandardMovementTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float SpecialMovementTime;

	FORCEINLINE FTimeSet(const float InStandardMovementTime = 0.f, const float InSpecialMovementTime = 0.f)
	{
		StandardMovementTime = InStandardMovementTime;
		SpecialMovementTime = InSpecialMovementTime;
	}
};


UCLASS(ClassGroup=(Turtles), meta=(BlueprintSpawnableComponent))
class TURTLES_API UTurtleComponent : public UMovementComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FVector TargetPoint;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	ENestMode Mode;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	UTurtlesWidget* Widget;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, meta=(ClampMin = -1.f, ClampMax = 1.f, UIMin = -1.f, UIMax = 1.f))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float MaxSpeed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float FloorCheckDistance;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FTimeSet ActiveTimeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeSets")
	FTimeSet StopsTimeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeSets")
	FTimeSet ReverseTimeSet;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bMovementStarted;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bTimerStarted;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bStandardMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* MovementSoundSample;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	UAudioComponent* MovementSound;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	UTurtleComponent();
	
	UFUNCTION(BlueprintCallable)
	virtual void SetTargetPoint(FVector InTargetPoint);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetMode(const ENestMode InMode);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetWidget(UTurtlesWidget* InWidget);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetDirection(const float InDirection);
	
	UFUNCTION(BlueprintCallable)
	virtual void Start();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "TurtleFinished"))
	void ReceiveFinish();
	
	virtual void Finish();

	UFUNCTION(BlueprintCallable)
	virtual void Move(const float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void TimerSignal();

	UFUNCTION(BlueprintCallable)
	virtual void TimerInit();

	UFUNCTION(BlueprintCallable)
	virtual void TimerStep(const float DeltaTime);
};
