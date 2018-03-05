// Property of DALAL

#include "ChoseNextWaypoint.h"
#include "PatrollingGuard.h"



EBTNodeResult::Type UChoseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Guard = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());

	///Sets the Patrol Route
	PatrolPoints = Guard->PatrolPointsCPP;
	BlackBoardComp->SetValueAsObject(NextWaypoint.SelectedKeyName, PatrolPoints[Index]);

	///Next Patrol Point
	Index = (Index + 1) % (PatrolPoints.Num());
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);
	
	return EBTNodeResult::Succeeded;
}
