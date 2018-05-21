// Fill out your copyright notice in the Description page of Project Settings.

#include "RecordsManager.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
#include "Engine.h"

TArray<TTuple<FString, FString>> ARecordsManager::RecordsScores;

// Sets default values
ARecordsManager::ARecordsManager() : Super(), CurrentScore(0)
{
	RecordsText = FString("");
	Name = FString("Default");
}

// Called when the game starts or when spawned
void ARecordsManager::BeginPlay()
{
	Super::BeginPlay();

	ARecordsManager::RecordsScores.Empty();

	MyIncreaseScore.BindLambda([this](int score) { OnScore(score); });

	// Load JSON data
	ReadJsonFile();


	for (int32 Index = 0; Index < RecordsScores.Num() && Index < 10; Index++)
	{
		FString Name = RecordsScores[Index].Key;
		FString Punctuation = RecordsScores[Index].Value;
		RecordsText += (Name + " :\t" + Punctuation + "\n");
	}


	// Create the Records Widget
	if (WRecords)
	{
		pWRecords = CreateWidget<UUserWidget>(GetGameInstance(), WRecords);
		if (pWRecords)
		{
			pWRecords->AddToViewport();
			pWRecordsText = (UTextBlock*)pWRecords->GetWidgetFromName("RecordText");
			pWScoreText = (UTextBlock*)pWRecords->GetWidgetFromName("PunctuationText");
			
			if (pWRecordsText != nullptr)
				pWRecordsText->SetText(FText::FromString(RecordsText));

			if (pWScoreText != nullptr)
				pWScoreText->SetText(FText::AsNumber(CurrentScore));
		}
	}
}

void ARecordsManager::OnScore(int score)
{
	CurrentScore += score;

	// Show punctuation in HUD
	if (pWScoreText != nullptr)
		pWScoreText->SetText(FText::AsNumber(CurrentScore));
}

void ARecordsManager::ReadJsonFile()
{
	if (RecordsScores.Num() != 0)
	{
		return;
	}
	// Read Json File into TMap
	FString FullPath = FPaths::ProjectDir() + "Content/Data/Records.json";
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = FJsonStringReader::Create(JsonStr);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> ObjArray = JsonObject->GetArrayField(TEXT("Records"));

		for (int32 i = 0; i < ObjArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> Value = ObjArray[i];
			TSharedPtr<FJsonObject> Json = Value->AsObject();

			FString Name = Json->GetStringField(TEXT("Name"));
			FString Score = Json->GetStringField(TEXT("Score"));

			// Add the values read, into corresponding arrays
			RecordsScores.Add(TTuple<FString, FString>(Name, Score));
		}
	}
}

void ARecordsManager::WriteJsonFile()
{
	// First of all, add the current punctuation to the array
	ARecordsManager::RecordsScores.Emplace(MakeTuple(Name, FString::FromInt(CurrentScore)));

	// Sort the array
	RecordsScores.Sort(ARecordsManager::ConstPredicate);

	// Main JSON object
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	// JSON Array to store Records object
	TArray<TSharedPtr<FJsonValue>> RecordsArray;

	// Record object. It has the following form:
	/*  {
			"Name":"the_name",
			"Score":"the_score"
		}
	*/

	for (int32 Index = 0; Index < RecordsScores.Num(); Index++)
	{
		TSharedPtr<FJsonObject> JsonRecordObject = MakeShareable(new FJsonObject());
		JsonRecordObject->SetStringField("Name", RecordsScores[Index].Key);
		JsonRecordObject->SetStringField("Score", RecordsScores[Index].Value);
		TSharedRef<FJsonValueObject> JsonValue = MakeShareable(new FJsonValueObject(JsonRecordObject));

		// Add the Record Object to JSON Array
		RecordsArray.Add(JsonValue);
	}


	// Add the JSON Array to main JSON Object
	JsonObject->SetArrayField("Records", RecordsArray);

	// Write JSON Object to JSON file
	FString FullPath = FPaths::ProjectDir() + "Content/Data/Records.json";
	FString JsonStr;
	TSharedRef< TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	FFileHelper::SaveStringToFile(*JsonStr, *FullPath);
}