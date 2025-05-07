#include "ItemCoordinates.h"

#include "ItemType.generated.h"

class UItemInstance;
/** Please add a class description */
UCLASS(Blueprintable, BlueprintType)
class UItemType : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FString Name;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int32 MaxDurability;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	TObjectPtr<UTexture2D> Icon;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FItemCoordinates InventorySize;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	TSubclassOf<UItemInstance> ItemInstanceClass;
};
