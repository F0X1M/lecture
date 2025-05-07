// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.h"

#include "ItemInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WYK_API UItemInstance : public UObject
{
public:
	GENERATED_BODY()

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	double Durability;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	FItemCoordinates PositionInEquipment;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	TObjectPtr<UItemType> ItemData;

};
