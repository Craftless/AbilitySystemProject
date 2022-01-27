// Fill out your copyright notice in the Description page of Project Settings.


#include "LeapCooldownMMC.h"
#include "AttributeSetBase.h"


ULeapCooldownMMC::ULeapCooldownMMC() 
{
    DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Agility, Source, true);

    RelevantAttributesToCapture.Add(AgilityDef);
}

float ULeapCooldownMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec & Spec) const
{

    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    float SourceAgility;
    FAggregatorEvaluateParameters Params;
    Params.SourceTags = SourceTags;
    Params.TargetTags = TargetTags;

    GetCapturedAttributeMagnitude(AgilityDef, Spec, Params, SourceAgility);
    float CooldownMultiplier = 1;
    if (SourceTags -> HasTagExact(FGameplayTag::RequestGameplayTag(FName("general.agilitypoison")))) {
        CooldownMultiplier *= 2;
    }


    return CooldownMultiplier * ((20 - 4) * exp(-0.1f * (SourceAgility * 0.5 + Spec.GetLevel())) + 4);
}
