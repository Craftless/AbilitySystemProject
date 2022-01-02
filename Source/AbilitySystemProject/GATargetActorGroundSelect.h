// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGroundSelect.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEMPROJECT_API AGATargetActorGroundSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:

	AGATargetActorGroundSelect();

	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	/** Requesting targeting data, but not necessarily stopping/destroying the task. Useful for external target data requests. */
	virtual void ConfirmTargetingAndContinue() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool GetLookPos(FVector& OutHitPoint);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	float Radius = 200.f;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UDecalComponent* DecalComp;
	USceneComponent* RootComp;

};
