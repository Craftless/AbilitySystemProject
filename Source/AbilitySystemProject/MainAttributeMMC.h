// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MainAttributeMMC.generated.h"



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
class ABILITYSYSTEMPROJECT_API UMainAttributeMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	
};
