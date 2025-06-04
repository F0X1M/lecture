// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FItem2DArray{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<int32> Ar;

	int32& operator[] (int32 i) {
		return Ar[i];
	}

	void Add(int32 rune) {
		Ar.Add(rune);
	}

	void Init(int32 size)
	{
		Ar.Init(-1, size);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemPickedUp);

UCLASS(Blueprintable)
class WYK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool GetFirstFreeSlot(FItemCoordinates ItemSize, FItemCoordinates& OutFoundCoordinates);

	UFUNCTION(BlueprintCallable)
	void SetItemInstanceAtPosition(int32 Index, FItemCoordinates NewPosition, FItemCoordinates ItemSize);

	UFUNCTION(BlueprintCallable)
	bool AddItem_Native(UItemType* ItemType);

	UFUNCTION(BlueprintCallable)
	bool AddItemInstance_Native(UItemInstance* ItemInstance);
	
	UFUNCTION(BlueprintCallable)
	UItemInstance* RemoveItemInstance_Native(UItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable)
	void DropItemInstance_Native(UItemInstance* ItemInstance);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D InventorySize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FItem2DArray> ItemArray;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UItemInstance>> Items;

	UPROPERTY(BlueprintAssignable)
	FOnItemPickedUp OnItemPickedUp;
};
