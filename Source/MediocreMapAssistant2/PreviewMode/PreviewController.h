// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteData.h"
#include "WallData.h"
#include "PreviewController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNoteNeedToSpawn, UNoteData*, p_NoteData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWallNeedToSpawn, UWallData*, p_NoteData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotesProcess, TArray<UNoteData*>, p_Notes);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWallsProcess, TArray<UWallData*>, p_Walls);

UCLASS()
class MEDIOCREMAPASSISTANT2_API APreviewController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreviewController();

private:

	float m_LastBeat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool m_Playing;

	float CurrentBeat;

	int m_NotesIndex;

	int m_WallsIndex;

	TArray<UNoteData*> m_Notes;

	TArray<UWallData*> m_Walls;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
		FOnNoteNeedToSpawn OnNoteNeedToSpawn;

	UPROPERTY(BlueprintAssignable)
		FOnWallNeedToSpawn OnWallNeedToSpawn;

	UFUNCTION()
		void OnNoteNeedToSpawnImpl(UNoteData* p_Data);

	UFUNCTION()
		void OnWallNeedToSpawnImpl(UWallData* p_Data);

	UFUNCTION()
		void OnNotesProcess(TArray<UNoteData*> p_Notes);

	UFUNCTION()
		void OnWallsProcess(TArray<UWallData*> p_Walls);

	UFUNCTION()
		void Reset();

	UFUNCTION()
		void SetBeat(float p_Beat);
};
