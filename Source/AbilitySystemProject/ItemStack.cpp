// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStack.h"
#include "ItemStructs.h"
#include "Item.h"
#include "UObject/UObjectGlobals.h"
#include "Characters/ProjectCharacter.h"

UItemStack::UItemStack(UItem* InItem, int32 InAmount) 
{
    Item = InItem;
    Amount = InAmount;
}

UItemStack::UItemStack(UItem* InItem) 
{
    Item = InItem;
    Amount = 1;
}

UItemStack::UItemStack() 
{
    
}

int32 UItemStack::GetEmptyStackID() 
{
    return 20193;
}

UItemStack* UItemStack::GetEmptyStack(UObject* Outer) 
{
    UItemStack* Stack = NewObject<UItemStack>(Outer, StaticClass());
    Stack -> MakeItemStackEmpty();
    return Stack;
}


bool UItemStack::UpdateStackEmptyStatus() 
{
    if (Amount <= 0) 
    {
        this ->  MakeItemStackEmpty();
        return true;
    }
    return false;
}

void UItemStack::MakeItemStackEmpty() 
{
    Amount = 0;
    Item = NewObject<UItem>(this, UItem::StaticClass());
    Item -> ItemInfo = FItemInfo();
}

UItemStack* UItemStack::AddToAmount(int32 AmountToAdd) 
{
    if (this == GetEmptyStack(this)) UE_LOG(LogTemp, Error, TEXT("Adding to empty stack"));
    Amount += AmountToAdd;
    UpdateStackEmptyStatus();
    return this;
}

UItemStack* UItemStack::SetStackItemAndAmount(UItem* ItemToSet, int32 AmountToSet) 
{
    Item = ItemToSet;
    Amount = AmountToSet;
    if (AmountToSet > 0)
        UpdateStackEmptyStatus();
    return this;
}

bool UItemStack::LeftoverAmount(UItemStack* StackToCheck, int32& LeftoverAmount, int32& AmountConsumed) 
{
    int32 AmountToCheck = StackToCheck -> Amount; // 100
    int32 AmountLeftToAdd = AmountToCheck;
    int32 MaxStackSize = StackToCheck -> Item -> ItemInfo.MaxStackSize; // 0
    if (Amount + AmountToCheck > MaxStackSize) {
        AmountConsumed = MaxStackSize - Amount;
        AmountLeftToAdd -= AmountConsumed;
        LeftoverAmount = AmountLeftToAdd;
        UE_LOG(LogTemp, Warning, TEXT("AmountToCheck: %i, MaxStackSize: %i, LeftoverAmount: %i, AmountConsumed: %i"), AmountToCheck, MaxStackSize, LeftoverAmount, AmountConsumed);
        return true;
    };
    AmountConsumed = AmountToCheck;
    LeftoverAmount = 0;
    return false;
}

UItemStack* UItemStack::Initialise(UItem* InItem, int32 InAmount) 
{
    MakeItemStackEmpty();
    if (!InItem) return this;
    Item = InItem;
    Amount = InAmount;
    return this;
}

bool UItemStack::IsFull() const
{
    UE_LOG(LogTemp, Warning, TEXT("Is Full, First: %f, Second: %f."), Amount, Item -> ItemInfo.MaxStackSize);
    return Amount >= Item -> ItemInfo.MaxStackSize;
}

void UItemStack::SetItem(UItem* ItemToSet) 
{
    Item = ItemToSet;
    UpdateStackEmptyStatus();
}

void UItemStack::UseItem(AProjectCharacter* User) 
{
    if (Amount <= 0) return;
    Item -> FOnFinishedUsing.AddUniqueDynamic(this, &UItemStack::FinishedUsing);
    Item -> UseItem(User);
    UE_LOG(LogTemp, Warning, TEXT("Entered first itemstack"));
}

void UItemStack::FinishedUsing(bool bSuccess) 
{
    if (bSuccess) {
        AddToAmount(-1);
    }
    Item -> FOnFinishedUsing.RemoveDynamic(this, &UItemStack::FinishedUsing);
}