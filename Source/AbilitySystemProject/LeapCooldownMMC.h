// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "LeapCooldownMMC.generated.h"



// -------------------------------------------------------------------------
//	Helper macros for declaring attribute captures 
// -------------------------------------------------------------------------

#define DECLARE_ATTRIBUTE_CAPTUREDEF(P) \
	FProperty* P##Property; \
	FGameplayEffectAttributeCaptureDefinition P##Def; \

#define DEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \
{ \
	P##Property = FindFieldChecked<FProperty>(S::StaticClass(), GET_MEMBER_NAME_CHECKED(S, P)); \
	P##Def = FGameplayEffectAttributeCaptureDefinition(P##Property, EGameplayEffectAttributeCaptureSource::T, B); \
}



/**
 * 
 */
UCLASS()
class ABILITYSYSTEMPROJECT_API ULeapCooldownMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	DECLARE_ATTRIBUTE_CAPTUREDEF(Agility);
	ULeapCooldownMMC();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec & Spec) const;
	
};
