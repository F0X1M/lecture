// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

USTRUCT()
struct FItem2DArray{
	GENERATED_BODY()
public:

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
	FVector2D GetFirstFreeSlot(FVector2D ItemSize);

	UFUNCTION(BlueprintCallable)
	void SetItemInstanceAtPosition(UItemInstance* ItemInstance, FVector2D NewPosition);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D InventorySize;

	TArray<FItem2DArray> ItemArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UItemInstance>> Items;

};
