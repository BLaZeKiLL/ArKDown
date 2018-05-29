// Property of DALAL

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "ChoseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class ARKDOWN_API UChoseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "BlackBoard")
		struct FBlackboardKeySelector IndexKey;

	UPROPERTY(EditAnywhere, Category = "BlackBoard")
		struct FBlackboardKeySelector NextWaypoint;

private:

	TArray<AActor*> PatrolPoints;

};
