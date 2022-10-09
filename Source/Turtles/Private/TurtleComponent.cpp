// Made by Maxim "RenViscoso" Levin for a test task from Fntastic


#include "TurtleComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


UTurtleComponent::UTurtleComponent()
{
	Direction = 1.f;
	MaxSpeed = 120.f;
	Timer = 0.f;
	StopsTimeSet.StandardMovementTime = 1.f;
	StopsTimeSet.SpecialMovementTime = 0.5f;
	ReverseTimeSet.StandardMovementTime = 1.f;
	ReverseTimeSet.SpecialMovementTime = 0.5f;
	FloorCheckDistance = 100.f;
	bMovementStarted = false;
	bTimerStarted = false;
	bStandardMovement = true;
}


void UTurtleComponent::SetTargetPoint(const FVector InTargetPoint)
{
	TargetPoint = InTargetPoint;
}


void UTurtleComponent::SetMode(const ENestMode InMode)
{
	Mode = InMode;
}


void UTurtleComponent::SetWidget(UTurtlesWidget* InWidget)
{
	Widget = InWidget;
}


void UTurtleComponent::SetDirection(const float InDirection)
{
	Direction = InDirection;
}


void UTurtleComponent::Start()
{
	if (IsValid(MovementSoundSample))
	{
		MovementSound = UGameplayStatics::SpawnSoundAttached(MovementSoundSample, GetOwner()->GetRootComponent());
	}
	bMovementStarted = true;
	if (Mode == ENestMode::Turtle_Standard)
	{
		return;
	}
	ActiveTimeSet = Mode == ENestMode::Turtle_WithStops ? StopsTimeSet : ReverseTimeSet;
	TimerInit();
	bTimerStarted = true;
}


void UTurtleComponent::Finish()
{
	Widget->TurtleFinished(Mode);
	MovementSound->Stop();
	GetOwner()->Destroy();
}


void UTurtleComponent::TimerSignal()
{
	float NewDirection;
	if (bStandardMovement)
	{
		if (Mode == ENestMode::Turtle_WithStops)
		{
			NewDirection = 0.f;
			if (MovementSound != nullptr)
			{
				MovementSound->SetPaused(true);
			}
		}
		else
		{
			NewDirection = -1.f;
		}
		bStandardMovement = false;
	}
	else
	{
		NewDirection = 1.f;
		if (MovementSound != nullptr)
		{
			MovementSound->SetPaused(false);
		}
		bStandardMovement = true;
	}
	Direction = NewDirection;
}


void UTurtleComponent::TimerInit()
{
	Timer = bStandardMovement ? ActiveTimeSet.StandardMovementTime : ActiveTimeSet.SpecialMovementTime;
}


void UTurtleComponent::TimerStep(const float DeltaTime)
{
	Timer -= DeltaTime;
	if (Timer > 0.f)
	{
		return;
	}
	TimerSignal();
	TimerInit();
}


void UTurtleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bMovementStarted)
	{
		return;
	}
	Move(DeltaTime);
	
	if (!bTimerStarted)
	{
		return;
	}
	TimerStep(DeltaTime);
}


void UTurtleComponent::Move(const float DeltaTime)
{
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + (FVector::DownVector * FloorCheckDistance);
	FHitResult HitResult;
	bool bTraced = GetWorld()->LineTraceSingleByChannel(HitResult,
		Start, End, ECollisionChannel::ECC_WorldStatic);
	if (bTraced)
	{
		FVector Normal = HitResult.ImpactNormal;
		float RotationCorrectionFloat = PI / 2.f;
		FRotator RotationCorrection = FRotator(RotationCorrectionFloat, RotationCorrectionFloat, RotationCorrectionFloat);
		FRotator Rotation = (RotationCorrection.RotateVector(Normal)).Rotation();
		GetOwner()->SetActorRotation(Rotation);
	}
	else
	{
		GetOwner()->SetActorRotation(FRotator::ZeroRotator);
	}
	float CurrentSpeed = DeltaTime * Direction * MaxSpeed;
	FVector DirectionToFinish = (TargetPoint - GetOwner()->GetActorLocation()).GetSafeNormal();
	Velocity = DirectionToFinish * CurrentSpeed;
	FRotator RotationToFinish = FRotator(0.f, 0.f, DirectionToFinish.Rotation().Roll);
	GetOwner()->AddActorWorldRotation(RotationToFinish);
}
