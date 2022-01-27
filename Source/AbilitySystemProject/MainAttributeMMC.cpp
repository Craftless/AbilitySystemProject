// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAttributeMMC.h"
#include "AttributeSetBase.h"


struct DamageStatics {
    DECLARE_ATTRIBUTE_CAPTUREDEF(HealthRegen)
    DECLARE_ATTRIBUTE_CAPTUREDEF(ManaRegen)
    DECLARE_ATTRIBUTE_CAPTUREDEF(StaminaRegen)

    DamageStatics() {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, HealthRegen, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, ManaRegen, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, StaminaRegen, Source, true);
    }
};

static DamageStatics& GetDamageStatics() {
    static DamageStatics DamageStaticsInst;
    return DamageStaticsInst;
}

