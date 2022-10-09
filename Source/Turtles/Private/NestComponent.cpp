// Made by Maxim "RenViscoso" Levin for a test task from Fntastic


#include "NestComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


UNestComponent::UNestComponent()
{
	SpawnCheckDistance = 500.f;
}

void UNestComponent::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> Components = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), RequiredTag);
	if (Components.Num() < 1)
	{
		UE_LOG(LogTemp, Fatal, TEXT("There is no spawnpoints in the actor!"));
	}
	SpawnPoint = Cast<USceneComponent>(Components[0]);
	if (SpawnPoint == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("USceneComponent is not USceneComponent. Wait, what?"));
	}
}



void UNestComponent::SetWidget(UTurtlesWidget* InWidget)
{
	Widget = InWidget;
}


void UNestComponent::SpawnTurtle()
{
	SpawnEffect();
	FActorSpawnParameters Params;
	Params.bAllowDuringConstructionScript = true;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	Params.OverrideLevel = GetOwner()->GetLevel();
	Params.Name = TurtleClass->GetFName();
	UE_LOG(LogTemp, Log, TEXT("Trying to get spawn transform"));
	FTransform SpawnTransform = GetSpawnTransform();
	UE_LOG(LogTemp, Log, TEXT("SUCCESS"));
	UE_LOG(LogTemp, Log, TEXT("Trying to spawn turtle"));
	if (!IsValid(TurtleClass))
	{
		UE_LOG(LogTemp, Error, TEXT("Ivalid turtle class!"));
		return;
	}
	AActor* Actor = GetWorld()->SpawnActor(TurtleClass, &SpawnTransform, Params);
	if (Actor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't spawn a turtle!"))
		Actor->Destroy();
		Widget->TurtleFinished(Mode);
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("SUCCESS"));
	UE_LOG(LogTemp, Log, TEXT("Trying to get a turtle component"));
	UActorComponent* Component = Actor->GetComponentByClass(UTurtleComponent::StaticClass());
	if (Component == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't get a turtle component!"))
		Actor->Destroy();
		Widget->TurtleFinished(Mode);
		return;
	}
	UTurtleComponent* TurtleComponent = Cast<UTurtleComponent>(Component);
	if (TurtleComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't get a turtle component!"))
		Actor->Destroy();
		Widget->TurtleFinished(Mode);
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("SUCCESS"));
	TurtleComponent->SetWidget(Widget);
	TurtleComponent->SetMode(Mode);
	if (!FinishPoint)
	{
		UE_LOG(LogTemp, Error, TEXT("Ivalid finish point!"));
		Actor->Destroy();
		Widget->TurtleFinished(Mode);
		return;
	}
	TurtleComponent->SetTargetPoint(FinishPoint->GetActorLocation());
	TurtleComponent->Start();
}


void UNestComponent::SpawnEffect()
{
	UParticleSystemComponent* Emitter =
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticlesSample, GetOwner()->GetTransform());
	Emitter->SetMaterial(0, ParticlesMaterial);
	UGameplayStatics::SpawnSoundAttached(SpawnSoundSample, Emitter);
}


FTransform UNestComponent::GetSpawnTransform() const
{
	FVector Start = SpawnPoint->GetComponentLocation();
	FVector End = Start + (FVector::DownVector * SpawnCheckDistance);
	FHitResult HitResult;
	bool bTraced = GetWorld()->LineTraceSingleByChannel(HitResult,
		Start, End, ECollisionChannel::ECC_WorldStatic);
	FTransform Result = SpawnPoint->GetComponentTransform();
	if (bTraced)
	{
		Result.SetLocation(HitResult.Location);
	}
	return Result;	
}

UTurtlesWidget* UNestComponent::GetWidget()
{
	return Widget;
}