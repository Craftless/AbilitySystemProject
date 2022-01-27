// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStructs.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class UItem;
class UItemSlot;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class ABILITYSYSTEMPROJECT_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	TArray<UItemSlot*> GetSlots();
	UFUNCTION(BlueprintCallable)
	TArray<UItemSlot*> SetSlots(TArray<UItemSlot*> InSlots);

	UFUNCTION(BlueprintCallable)
	bool AddItemStackToSlots(UItemStack* ItemStackToAdd);
	UFUNCTION(BlueprintCallable)
	bool TryAddItemStackToSlot(UItemSlot* SlotToCheck, UItemStack* ItemStackToAdd, bool bSimulate = false);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxSlots;

	UFUNCTION(BlueprintImplementableEvent)
	void FinishedBeginPlay();

	UFUNCTION(BlueprintPure)
	bool CanContainItemStack(UItemStack* StackToCheck);

	UFUNCTION(BlueprintImplementableEvent)
	void Debug(float Thing1, UItemStack* Thing2);


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<UItemSlot*> Slots;

		
};
