// Property of DALAL

#include "ChoseNextWaypoint.h"



EBTNodeResult::Type UChoseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Guard = OwnerComp.GetAIOwner()->GetPawn();
	///PROTECTION
	if (!ensure(Guard)){ return EBTNodeResult::Failed; }

	///Sets the Patrol Route
	
	/*
	FindComponentByClass is a template function so it does not require casting
	in most cases when only a single component is to be used find is better
	cases where a parent of tow component is get then GetComponentByClass is better as it can be casted to children
	needless to say GetComponentBy class returns a UActorComponent* where as Find returns T*
	*/

	PatrolPoints = Guard->FindComponentByClass<UPatrolRoute>()->GetPatrolPoints();
	//PatrolPoints = Cast<UPatrolRoute>(Guard->GetComponentByClass(UPatrolRoute::StaticClass()))->GetPatrolPoints();

	///NO PATROL ROUTE
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("0 Patrol Points"));
		return EBTNodeResult::Failed;
	}

	///SET THE PATROL POINT
	BlackBoardComp->SetValueAsObject(NextWaypoint.SelectedKeyName, PatrolPoints[Index]);

	///Next Patrol Point
	Index = (Index + 1) % (PatrolPoints.Num());
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);
	
	return EBTNodeResult::Succeeded;
}
