// Property of DALAL

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector SpawnPoint;
	float Rotation;
	float Scale;
};

UCLASS()
class ARKDOWN_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Generation")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500.0f, float MinScale = 1.f, float MaxScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Generation")
		void PlaceAI(TSubclassOf<APawn> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500.0f);

	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(UActorPool* Pool);

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500.0f, float MinScale = 1.f, float MaxScale = 1.f);

	void PositionNavMeshBoundsVoulme(UActorPool* Pool);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptySpawnPoint(FVector& OutLocation, float Radius);

	void SpawnActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	void SpawnActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
};


