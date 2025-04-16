// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	ItemArray.Init({}, InventorySize.X);
	for (int i = 0; i < ItemArray.Num(); i++)
	{
		ItemArray[i].Init(InventorySize.Y);
	}

	Super::BeginPlay();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool CanInsert(TArray<FItem2DArray>& Items, int32 x, int32 y, FVector2d size)
{
	for (int lx = 0; lx < size.X; lx++)
	{
		for (int ly = 0; ly < size.Y; ly++)
		{
			int nx = lx + x;
			int ny = ly + y;

			if (Items[x][y] != -1)
				return false;
		}
	}

	return true;
}

FVector2D UInventoryComponent::GetFirstFreeSlot(FVector2D ItemSize)
{
	for (int x = 0; x < InventorySize.X - ItemSize.X; x++)
	{
		for (int y = 0; y < InventorySize.Y - ItemSize.Y; y++)
		{
			if (ItemArray[x][y] == -1)
				continue;

			if (CanInsert(ItemArray,x,y,ItemSize))
				return FVector2D(x,y);
		}
	}
	
	return FVector2D(-1,-1);
}

void UInventoryComponent::SetItemInstanceAtPosition(UItemInstance* ItemInstance, FVector2D NewPosition)
{
	ItemArray[NewPosition.X][NewPosition.Y] = Items.Find(ItemInstance);
}

