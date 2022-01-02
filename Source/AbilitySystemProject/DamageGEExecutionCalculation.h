// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageGEExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEMPROJECT_API UDamageGEExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UDamageGEExecutionCalculation();

	FProperty* HealthProperty;
	FGameplayEffectAttributeCaptureDefinition HealthDef;

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
	
};
