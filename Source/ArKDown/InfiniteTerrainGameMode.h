// Property of DALAL

#pragma once

#include "CoreMinimal.h"
#include "ArKDownGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"


class ANavMeshBoundsVolume;

/**
 * 
 */
UCLASS()
class ARKDOWN_API AInfiniteTerrainGameMode : public AArKDownGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
		void PopulateBoundsVolumePool();

private:

	void AddToPool(ANavMeshBoundsVolume* VolumeToAdd);
	
	
};
