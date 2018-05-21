/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateCombinations.h"
#include "RecordsManager.generated.h"

UCLASS()
class AEROFIGHTERS_API ARecordsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecordsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FString RecordsText;

	int CurrentScore;
	FString Name;

	void OnScore(int score);

public:

	// Widget to show the records
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> WRecords;

	UPROPERTY()
		class UUserWidget* pWRecords;

	UPROPERTY()
		class UTextBlock* pWRecordsText;

	UPROPERTY()
		class UTextBlock* pWScoreText;

	static TArray<TTuple<FString, FString>> RecordsScores;

	void ReadJsonFile();

	UFUNCTION(BlueprintCallable)
		void SetName(FString Name_) { Name = Name_; }

	UFUNCTION(BlueprintCallable)
		int GetScore() { return CurrentScore; }

	UFUNCTION(BlueprintCallable)
		void WriteJsonFile();

	UFUNCTION(BlueprintCallable)
		void DeleteRecords();

	// Delegate to receive the punctuation
	DECLARE_DELEGATE_OneParam(FScoreIncreased, int);
	FScoreIncreased MyIncreaseScore;

	inline static bool ConstPredicate(const TTuple<FString, FString>& ip1, const TTuple<FString, FString>& ip2)
	{
		int32 val1 = FCString::Atoi(*ip1.Value);
		int32 val2 = FCString::Atoi(*ip2.Value);
		return (val1 > val2);
	}

};
