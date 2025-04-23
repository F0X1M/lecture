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

bool CanInsert(TArray<FItem2DArray>& Items, int32 x, int32 y, FItemCoordinates size)
{
	for (uint32 lx = 0; lx < size.X; lx++)
	{
		for (uint32 ly = 0; ly < size.Y; ly++)
		{
			int nx = lx + x;
			int ny = ly + y;

			if (Items[nx][ny] != -1)
				return false;
		}
	}

	return true;
}

bool UInventoryComponent::GetFirstFreeSlot(FItemCoordinates ItemSize, FItemCoordinates& OutFoundCoordinates)
{
	for (int x = 0; x < InventorySize.X - ItemSize.X; x++)
	{
		for (int y = 0; y < InventorySize.Y - ItemSize.Y; y++)
		{
			if (ItemArray[x][y] != -1)
				continue;

			if (CanInsert(ItemArray,x,y,ItemSize))
			{
				OutFoundCoordinates = FItemCoordinates(x,y);
				return true;
			}
			
		}
	}
	
	return false;
}

void UInventoryComponent::SetItemInstanceAtPosition(UItemInstance* ItemInstance, FItemCoordinates NewPosition, FItemCoordinates ItemSize)
{
	if (!ItemInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item instance was null"));
		return;
	}

	auto ItemSearchResult = Items.Find(ItemInstance);


	if (ItemSearchResult == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item was not found in Items array"));
		return;
	}

	for (uint32 x = NewPosition.X; x < ItemSize.X + NewPosition.X; x++)
	{
		for (uint32 y = NewPosition.Y; y < ItemSize.Y + NewPosition.Y; y++)
		{
			ItemArray[x][y] = ItemSearchResult;
		}
	}
}

