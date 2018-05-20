// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Boss.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API ABossAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	/*A Behavior tree component in order to be able to call specific functions like starting our BT*/
	UBehaviorTreeComponent * BehaviorTreeComp;

	/*A Blackboard component which will be used to initialize our Blackboard Values*/
	UBlackboardComponent* BlackboardComp;

	/*This property is used to find a certain key for our blackboard.
	We will create the blackboard later in this tutorial*/
	UPROPERTY(EditDefaultsOnly)
		FName TargetKey = "SensedPawn";
	

public:
	ABossAIController();

	virtual void Possess(APawn* InPawn) override;




};
