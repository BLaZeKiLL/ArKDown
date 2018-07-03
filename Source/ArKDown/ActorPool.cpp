// Property of DALAL

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

AActor* UActorPool::Checkout()
{
	if (Pool.Num() == 0)
	{
		return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("Item checked out"));
	return Pool.Pop();
}

void UActorPool::Return(AActor* ActorToReturn)
{
	Add(ActorToReturn);
}

void UActorPool::Add(AActor* ActorToAdd)
{
	if (!ActorToAdd)
	{
		UE_LOG(LogTemp, Warning, TEXT("null added"));
		return;
	}
	Pool.Push(ActorToAdd);
	UE_LOG(LogTemp, Warning, TEXT("Item added"));
}

