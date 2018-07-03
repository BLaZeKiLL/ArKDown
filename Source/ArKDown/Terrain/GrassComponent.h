// Property of DALAL

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class ARKDOWN_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UGrassComponent();

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
		FBox SpawningExtents;
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
		int SpawnCount;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void SpawnGrass();
	
	
};
