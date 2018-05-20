// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"

ABossAIController::ABossAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void ABossAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	//If our character is valid and has a valid Behavior Tree,
	//Initialize the values of the Blackboard and start the tree
	ABoss* Char = Cast<ABoss>(InPawn);
	if (Char && Char->BehaviorTree && Char->BehaviorTree->BlackboardAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("OJO!"));
		//Initialize the blackboard values
		BlackboardComp->InitializeBlackboard(*Char->BehaviorTree->BlackboardAsset);

		//Start the tree
		BehaviorTreeComp->StartTree(*Char->BehaviorTree);

	}

}
