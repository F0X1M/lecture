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

bool CanInsert(TArray<FItem2DArray>& Items, int x, int y, FItemCoordinates size)
{
	for (int ly = 0; ly < size.Y; ly++)
	{
		for (int lx = 0; lx < size.X; lx++)
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
	for (int y = 0; y < InventorySize.Y - ItemSize.Y + 1; y++)
	{
		for (int x = 0; x < InventorySize.X - ItemSize.X + 1; x++)
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

void UInventoryComponent::SetItemInstanceAtPosition(int32 Index, FItemCoordinates NewPosition, FItemCoordinates ItemSize)
{
	for (int y = NewPosition.Y; y < ItemSize.Y + NewPosition.Y; y++)
	{
		for (int x = NewPosition.X; x < ItemSize.X + NewPosition.X; x++)
		{
			ItemArray[x][y] = Index;
		}
	}
}

bool UInventoryComponent::AddItem_Native(UItemType* ItemType)
{
	auto inst = NewObject<UItemInstance>(GetOuter(), ItemType->ItemInstanceClass);
	return AddItemInstance_Native(inst);
}

bool UInventoryComponent::AddItemInstance_Native(UItemInstance* ItemInstance)
{
	FItemCoordinates FoundCoords;
	if (!GetFirstFreeSlot(ItemInstance->ItemData->InventorySize, FoundCoords))
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldnt add item"));
		return false;
	}

	auto idx = Items.Add(ItemInstance);
	ItemInstance->PositionInEquipment = FoundCoords;
	SetItemInstanceAtPosition(idx, ItemInstance->PositionInEquipment, ItemInstance->ItemData->InventorySize);

	OnItemPickedUp.Broadcast();
	return true;
}

UItemInstance* UInventoryComponent::RemoveItemInstance_Native(UItemInstance* ItemInstance)
{
	if (!ItemInstance)
		return nullptr;
	
	// TODO: fix
	this->Items.Remove(ItemInstance);
	SetItemInstanceAtPosition(-1, ItemInstance->PositionInEquipment, ItemInstance->ItemData->InventorySize);
	return nullptr;
}

void UInventoryComponent::DropItemInstance_Native(UItemInstance* ItemInstance)
{
	
}

