// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActorGetSurrounding.h"
#include "Abilities/GameplayAbility.h"


void AGATargetActorGetSurrounding::StartTargeting(UGameplayAbility* Ability) 
{
    Super::StartTargeting(Ability);
    MasterPC = Cast<APlayerController>(Ability -> GetOwningActorFromActorInfo() -> GetInstigatorController());
}

void AGATargetActorGetSurrounding::ConfirmTargetingAndContinue() 
{
    if (!ensure(MasterPC)) return;
    APawn* MasterPawn = MasterPC -> GetPawn();
    if (!MasterPawn) { TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle()); return; }

    FVector TargetPoint = MasterPawn -> GetActorLocation();
    TArray<FOverlapResult> Overlapped;
    TArray<TWeakObjectPtr<AActor>> OverlappedActors;
    FCollisionQueryParams Params;
    Params.bTraceComplex = false;
    Params.bReturnPhysicalMaterial = false;
    Params.AddIgnoredActor(MasterPawn -> GetUniqueID());

    bool bSuccess = GetWorld() -> OverlapMultiByObjectType(Overlapped, TargetPoint, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(Radius), Params);
    if (bSuccess) {
        for (int32 i = 0; i < Overlapped.Num(); i++) {
            APawn* OverlappedPawn = Cast<APawn>(Overlapped[i].GetActor());
            if (OverlappedPawn && !OverlappedActors.Contains(OverlappedPawn)) {
                OverlappedActors.Add(OverlappedPawn);
            }
        }
    }


    if (OverlappedActors.Num() > 0) {
        FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
        TargetDataReadyDelegate.Broadcast(TargetData);
    }
    else {
        TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
    }
    
}
