// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemStack.generated.h"

/**
 * 
 */

class UItem;
class UTexture2D;

USTRUCT(BlueprintType)
struct FItemInfo {
	GENERATED_BODY()

	FItemInfo() {
		Name = TEXT("None");
		Description = TEXT("No Description");
		ItemClass = nullptr;
		bIsStackable = true;
		MaxStackSize = 0;
		IconTexture = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = TEXT("None");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description = TEXT("No Description");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItem> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackable = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize = 16;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconTexture = nullptr;


};






UCLASS( BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABILITYSYSTEMPROJECT_API UItemStack : public UObject
{
	GENERATED_BODY()
	
public:
	UItemStack(UItem* InItem, int32 InAmount);

	UItemStack(UItem* InItem);

	UItemStack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItem* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID = 0;

	static UItemStack* GetEmptyStack(UObject* Outer);
	static int32 GetEmptyStackID();

	UFUNCTION(BlueprintCallable)
	bool UpdateStackEmptyStatus();

	UFUNCTION(BlueprintCallable)
	void MakeItemStackEmpty();

	UFUNCTION(BlueprintCallable)
	UItemStack* AddToAmount(int32 AmountToAdd);

	UFUNCTION(BlueprintCallable)
	UItemStack* SetStackItemAndAmount(UItem* ItemToSet, int32 AmountToSet);

	UFUNCTION(BlueprintCallable)
	bool LeftoverAmount(UItemStack* StackToCheck, int32& LeftoverAmount, int32& AmountConsumed);

	UFUNCTION(BlueprintCallable)
	UItemStack* Initialise(UItem* InItem, int32 InAmount);

	UFUNCTION(BlueprintPure)
	bool IsFull() const;

	UFUNCTION(BlueprintCallable)
	void SetItem(UItem* ItemToSet);

	UFUNCTION(BlueprintCallable)
	void UseItem(class AProjectCharacter* User);

	UFUNCTION()
	void FinishedUsing(bool bSuccess);
};
