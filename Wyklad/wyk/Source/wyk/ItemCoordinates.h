#pragma once

#include "ItemCoordinates.generated.h"

USTRUCT(BlueprintType)
struct FItemCoordinates
{
public:
	GENERATED_BODY()

	FItemCoordinates() = default;
	FItemCoordinates(int X, int Y) : X(X), Y(Y){};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Y;
};