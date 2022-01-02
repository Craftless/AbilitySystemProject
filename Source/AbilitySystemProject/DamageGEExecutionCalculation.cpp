// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageGEExecutionCalculation.h"
#include "AttributeSetBase.h"


struct DamageStatics {
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage)
    DECLARE_ATTRIBUTE_CAPTUREDEF(Armour)

    DamageStatics() {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, AttackDamage, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armour, Target, true);
    }
};

static DamageStatics& GetDamageStatics() {
    static DamageStatics DamageStaticsInst;
    return DamageStaticsInst;
}



UDamageGEExecutionCalculation::UDamageGEExecutionCalculation() 
{
    HealthProperty = FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health));
    HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, true);

    RelevantAttributesToCapture.Add(HealthDef);
    RelevantAttributesToCapture.Add(GetDamageStatics().AttackDamageDef);
    RelevantAttributesToCapture.Add(GetDamageStatics().ArmourDef);
}

void UDamageGEExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    float SourceAttackDamage;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().AttackDamageDef, FAggregatorEvaluateParameters(), SourceAttackDamage);
    float TargetArmour;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmourDef, FAggregatorEvaluateParameters(), TargetArmour);


    float FinalDamage = SourceAttackDamage * (1 - ((0.02f * TargetArmour) / (0.9f + 0.048f * TargetArmour)));

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}


