// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerArea.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerArea : public UBoxComponent
{
	GENERATED_BODY()
public:
	UTriggerArea();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called Every Frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

private:
	UPROPERTY(EditAnywhere)
	FName GargoyleTag;

	UMover* Mover;

	AActor* GetAcceptableActor();
};
