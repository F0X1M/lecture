#pragma once

#include "ItemCoordinates.generated.h"

USTRUCT(BlueprintType)
struct FItemCoordinates
{
public:
	GENERATED_BODY()

	FItemCoordinates() = default;
	FItemCoordinates(uint32_t X, uint32_t Y) : X(X), Y(Y){};

	UPROPERTY(EditAnywhere)
	uint32 X;

	UPROPERTY(EditAnywhere)
	uint32 Y;
};