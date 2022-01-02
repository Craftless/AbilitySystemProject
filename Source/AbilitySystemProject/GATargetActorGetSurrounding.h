// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGetSurrounding.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEMPROJECT_API AGATargetActorGetSurrounding : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	/** Requesting targeting data, but not necessarily stopping/destroying the task. Useful for external target data requests. */
	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	float Radius = 200.f;
	
};
