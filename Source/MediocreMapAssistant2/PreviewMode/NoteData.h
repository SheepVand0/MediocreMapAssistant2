// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoteData.generated.h"

UENUM()
enum class ENoteType : uint8 {
	LeftNote = 0,
	RightNote = 1,
	Bomb = 3
};

UENUM()
enum class ENoteCutDirection : uint8 {
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3,
	UpLeft = 4,
	UpRight = 5,
	DownLeft = 6,
	DownRight = 7,
	Any = 8
};


/**
 * 
 */
UCLASS()
class MEDIOCREMAPASSISTANT2_API UNoteData : public UObject
{

	GENERATED_BODY()

public:
	UNoteData();
	~UNoteData();
	
	UPROPERTY(BlueprintReadWrite)
		ENoteType NoteType;

	UPROPERTY()
		ENoteCutDirection CutDirection;

	UPROPERTY(BlueprintReadWrite)
		float Beat;

	UPROPERTY(BlueprintReadWrite)
		int LineIndex;

	UPROPERTY(BlueprintReadWrite)
		int LineLayer;
	 
	UFUNCTION(BlueprintCallable)
		void SetCutDirectionFromInt(int p_Direction);

	UFUNCTION(BlueprintCallable)
		ENoteCutDirection GetCutDirectionFromInt(int p_Direction);

	UFUNCTION(BlueprintCallable)
		void SetData(ENoteType p_NoteType, ENoteCutDirection p_CutDirection, float p_Beat, int p_LineIndex, int p_LineLayer);
		
};
