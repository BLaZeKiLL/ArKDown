// Property of DALAL

#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptySpawnPoint(SpawnPoint, Radius * RandomScale);
		if (found)
		{
			float RandomRodation = FMath::RandRange(-180.f, 180.f);
			SpawnActor(ToSpawn, SpawnPoint, RandomRodation, RandomScale);
		}
	}
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
		UE_LOG(LogTemp, Warning, TEXT("Pool Empty"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("poisitioning"));
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
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

	// Debug Sphere
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

void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0,Rotation,0));
	Spawned->SetActorScale3D(FVector(Scale));
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->Return(NavMeshBoundsVolume);
}

