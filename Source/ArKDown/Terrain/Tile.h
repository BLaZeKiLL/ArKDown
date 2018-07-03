// Property of DALAL

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

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
	
private:

	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptySpawnPoint(FVector& OutLocation, float Radius);

	void SpawnActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale);
};
