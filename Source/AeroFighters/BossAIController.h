/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Possess(APawn* InPawn) override;

private:
	ABoss* BossReference;



};
