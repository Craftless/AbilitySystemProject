// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemStack.h"
#include "Engine/Texture2D.h"





// USTRUCT(BlueprintType)
// struct FItemStack {
// 	GENERATED_USTRUCT_BODY()

// 	FItemStack(UItem* InItem, int32 InAmount) {
// 		Item = InItem;
// 		Amount = InAmount;
// 	}

// 	FItemStack(UItem* InItem) {
// 		Item = InItem;
// 		Amount = 1;
// 	}

// 	FItemStack() {
// 		Amount = 0;
// 		UItem = UItem::None;
// 	}

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	UItem* Item;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	int32 Amount;

// 	static FItemStack& EMPTY = FItemStack();

// 	bool UpdateStackEmptyStatus() {
// 		if (Amount <= 0) 
// 		{
// 			this = EMPTY;
// 			return true;
// 		}
// 		return false;
// 	}



// 	void AddToAmount(int32 AmountToAdd) {
// 		Amount += AmountToAdd;
// 		UpdateStackEmptyStatus();
// 	}
// };



// USTRUCT(BlueprintType)
// struct FItemSlot {
// 	GENERATED_USTRUCT_BODY()

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	UItemStack* ItemStack;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	bool GetIsEmpty() {
// 		if (ItemStack != ItemStack::EMPTY) return UpdateStackEmptyStatus(); 
// 		return true;
// 	}

// 	Texture2D* GetTexture() {
// 		return ItemStack -> Item -> IconTexture;
// 	}
	
// 	int32 GetStackSize() {
// 		return ItemStack -> Amount;
// 	}
// };



