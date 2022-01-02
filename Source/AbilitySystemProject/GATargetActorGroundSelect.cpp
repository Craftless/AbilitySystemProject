// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActorGroundSelect.h"
#include "Abilities/GameplayAbility.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"




AGATargetActorGroundSelect::AGATargetActorGroundSelect() {
    PrimaryActorTick.bCanEverTick = true;

    Radius = 200.f;

    RootComp = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));
    SetRootComponent(RootComp);
    DecalComp = CreateDefaultSubobject<UDecalComponent>(FName("Decal Component"));
    DecalComp -> SetupAttachment(RootComp);

    DecalComp -> DecalSize = FVector(Radius);
}

void AGATargetActorGroundSelect::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    FVector LookPos;
    if (GetLookPos(LookPos)) {
        DecalComp -> SetWorldLocation(LookPos);
    }
}


void AGATargetActorGroundSelect::StartTargeting(UGameplayAbility* Ability) 
{
    Super::StartTargeting(Ability);
    MasterPC = Cast<APlayerController>(Ability -> GetOwningActorFromActorInfo() -> GetInstigatorController());
}

void AGATargetActorGroundSelect::ConfirmTargetingAndContinue() 
{
    if (!ensure(MasterPC)) return;
    APawn* MasterPawn = MasterPC -> GetPawn();
    if (!MasterPawn) return;

    FVector LookPoint = FVector();
    if (GetLookPos(LookPoint)) {
        TArray<FOverlapResult> Overlapped;
        TArray<TWeakObjectPtr<AActor>> OverlappedActors;
        FCollisionQueryParams Params;
        Params.bTraceComplex = false;
        Params.bReturnPhysicalMaterial = false;
        Params.AddIgnoredActor(MasterPawn -> GetUniqueID());

        bool bSuccess = GetWorld() -> OverlapMultiByObjectType(Overlapped, LookPoint, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(Radius), Params);
        if (bSuccess) {
            for (int32 i = 0; i < Overlapped.Num(); i++) {
                APawn* OverlappedPawn = Cast<APawn>(Overlapped[i].GetActor());
                if (OverlappedPawn && !OverlappedActors.Contains(OverlappedPawn)) {
                    OverlappedActors.Add(OverlappedPawn);
                }
            }
        }

        FGameplayAbilityTargetData_LocationInfo* TargetPos = new FGameplayAbilityTargetData_LocationInfo();
        if (DecalComp) {
            TargetPos -> TargetLocation.LiteralTransform = DecalComp -> GetComponentTransform();
            TargetPos -> TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
        }


        if (OverlappedActors.Num() > 0) {
            FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
            TargetData.Add(TargetPos);
            TargetDataReadyDelegate.Broadcast(TargetData);
        }
        else {
            TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle(TargetPos));
        }
    }
}


bool AGATargetActorGroundSelect::GetLookPos(FVector& OutHitPoint) 
{
    if (!ensure(MasterPC)) return false;
    APawn* MasterPawn = MasterPC -> GetPawn();
    if (!MasterPawn) return false;
    FVector VPPos;
    FRotator VPRot;
    MasterPC -> GetPlayerViewPoint(VPPos, VPRot);
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.bTraceComplex = true;
    Params.AddIgnoredActor(MasterPawn -> GetUniqueID());
    bool bSuccess = GetWorld() -> LineTraceSingleByChannel(HitResult, VPPos, VPPos + VPRot.Vector() * 10000.f, ECC_Visibility, Params);
    if (bSuccess) {
        OutHitPoint = HitResult.ImpactPoint;
        return true;
    }
    return false;
}
