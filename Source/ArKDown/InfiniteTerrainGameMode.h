// Property of DALAL

#pragma once

#include "CoreMinimal.h"
#include "ArKDownGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"


class ANavMeshBoundsVolume;
class UActorPool;

/**
 * 
 */
UCLASS()
class ARKDOWN_API AInfiniteTerrainGameMode : public AArKDownGameMode
{
	GENERATED_BODY()
	
public:

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
		void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
		UActorPool * NavMeshBoundsVolumePool;

private:

	void AddToPool(ANavMeshBoundsVolume* VolumeToAdd);
	

};
