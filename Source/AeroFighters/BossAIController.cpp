// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"

ABossAIController::ABossAIController() : BossReference(nullptr)
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void ABossAIController::Tick(float DeltaTime)
{
	if (BossReference)
	{
		FName key = FName("Hp");

		BlackboardComp->SetValueAsFloat(key, BossReference->GetHp());
	}
}

void ABossAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	//If our character is valid and has a valid Behavior Tree,
	//Initialize the values of the Blackboard and start the tree
	ABoss* Char = Cast<ABoss>(InPawn);
	if (Char && Char->BehaviorTree && Char->BehaviorTree->BlackboardAsset)
	{
		BossReference = Char;

		//Initialize the blackboard values
		BlackboardComp->InitializeBlackboard(*Char->BehaviorTree->BlackboardAsset);

		//Start the tree
		BehaviorTreeComp->StartTree(*Char->BehaviorTree);

		FName key = FName("Character");
	
		uint8 keyid = BlackboardComp->GetKeyID(key);
		
		BlackboardComp->SetValueAsObject(key, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

}
