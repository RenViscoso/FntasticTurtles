// Made by Maxim "RenViscoso" Levin for a test task from Fntastic

#pragma once

#include "CoreMinimal.h"
#include "NestModeEnum.h"
#include "TurtleComponent.h"
#include "TurtlesWidget.h"
#include "Components/ActorComponent.h"
#include "NestComponent.generated.h"


/**
 * The component for spawn turtles. Required sibling component with a tag "SpawnTurtles"
 */

UCLASS(ClassGroup=(Turtles), meta=(BlueprintSpawnableComponent))
class TURTLES_API UNestComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	const FName RequiredTag = "SpawnTurtles";
	
	/** The spawn point component */
	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly)
	USceneComponent* SpawnPoint;

	/** The spawn point component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float SpawnCheckDistance;

	/** The finish point actor */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	AActor* FinishPoint;

	/** The mode of nest */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ENestMode Mode;

	/** The widget with buttons */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	UTurtlesWidget* Widget;

	/** The sampler to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> TurtleClass;
	
	/** The particles for spawn */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParticleSystem* ParticlesSample;

	/** The material of particles for spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* ParticlesMaterial;
	
    /** The sound for spawn */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* SpawnSoundSample;

	virtual void BeginPlay() override;
	
public:

	UNestComponent();

	UFUNCTION(BlueprintCallable)
	virtual void SetWidget(UTurtlesWidget* InWidget);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual ENestMode GetMode() const { return Mode; }

	UFUNCTION(BlueprintCallable)
	virtual void SpawnTurtle();

	UFUNCTION(BlueprintCallable)
	virtual void SpawnEffect();

	/** This one checks ground Z level */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FTransform GetSpawnTransform() const;
	
	UFUNCTION(BlueprintCallable)
	virtual UTurtlesWidget* GetWidget();
};
