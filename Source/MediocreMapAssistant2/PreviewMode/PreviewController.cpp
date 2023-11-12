// Fill out your copyright notice in the Description page of Project Settings.

#include "PreviewController.h"


// Sets default values
APreviewController::APreviewController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APreviewController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APreviewController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_Playing) return;

	

	m_LastBeat = CurrentBeat;
}

void APreviewController::OnNoteNeedToSpawnImpl(UNoteData* p_Data) {

}

void APreviewController::OnWallNeedToSpawnImpl(UWallData* p_Data) {

}

void APreviewController::OnNotesProcess(TArray<UNoteData*> p_Notes) {
	m_Notes = p_Notes;
}

void APreviewController::OnWallsProcess(TArray<UWallData*> p_Walls) {
	m_Walls = p_Walls;
}

void APreviewController::Reset() {
	CurrentBeat = 0;
	m_WallsIndex = 0;
	m_NotesIndex = 0;
	m_Notes.Empty();
	m_Walls.Empty();
}

void APreviewController::SetBeat(float p_Time) {
	CurrentBeat = p_Time;
	for (int l_i = 0; l_i < m_Notes.Num(); l_i++) {
		if (m_Notes[l_i]->Beat >= p_Time) {
			m_NotesIndex = l_i;
			break;
		}
	}

	for (int l_i = 0; l_i < m_Walls.Num(); l_i++) {
		float l_Beat = m_Walls[l_i]->Beat;
		if (l_Beat >= p_Time - FMath::Clamp(0.0f, m_Walls[l_i]->Duration, m_Walls[l_i]->Duration - (p_Time - l_Beat))) {
			m_WallsIndex = l_i;
			break;
		}
	}
}