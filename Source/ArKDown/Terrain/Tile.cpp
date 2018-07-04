// Property of DALAL

#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Engine/World.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	CanSpawnAtLocation(GetActorLocation(), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Needs to be above where it is used , blame C++
template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn /*= 1*/, int MaxSpawn /*= 1*/, float Radius /*= 500.0f*/, float MinScale /*= 1.f*/, float MaxScale /*= 1.f*/)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptySpawnPoint(SpawnPosition.SpawnPoint, Radius * SpawnPosition.Scale);
		if (found)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnActor(ToSpawn, SpawnPosition);
		}
	}
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
}

void ATile::PlaceAI(TSubclassOf<APawn> ToSpawn, int MinSpawn /*= 1*/, int MaxSpawn /*= 1*/, float Radius /*= 500.0f*/)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius, 1.f, 1.f);
}

void ATile::SetPool(UActorPool* Pool)
{
	this->Pool = Pool;

	PositionNavMeshBoundsVoulme(Pool);
}

void ATile::PositionNavMeshBoundsVoulme(UActorPool* Pool)
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (!NavMeshBoundsVolume)
	{
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	//Debug Sphere
	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(
	//	GetWorld(),
	//	GlobalLocation,
	//	0,
	//	Radius,
	//	FQuat::Identity,
	//	ResultColor,
	//	true,
	//	100
	//);

	return !HasHit;
}

bool ATile::FindEmptySpawnPoint(FVector& OutLocation, float Radius)
{
	FVector min(0, -2000, 0);
	FVector max(4000, 2000, 0);
	FBox Bounds(min, max);

	const int MAX_ATTEMPTS = 100;
	for (int i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint,Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}

	return false;
}

void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (!Spawned) { return; }

	Spawned->SetActorRelativeLocation(SpawnPosition.SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation,0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::SpawnActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	if (!Spawned) { return; }

	Spawned->SetActorRelativeLocation(SpawnPosition.SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("Enemy"));

}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->Return(NavMeshBoundsVolume);
}

