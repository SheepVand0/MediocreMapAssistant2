// Fill out your copyright notice in the Description page of Project Settings.

#include "NoteData.h"

UNoteData::UNoteData()
{

}

UNoteData::~UNoteData()
{

}

void UNoteData::SetCutDirectionFromInt(int p_NoteData) {
	CutDirection = GetCutDirectionFromInt(p_NoteData);
}

ENoteCutDirection UNoteData::GetCutDirectionFromInt(int p_Value) {
	return (ENoteCutDirection)p_Value;
}

void UNoteData::SetData(ENoteType p_NoteType, ENoteCutDirection p_CutDirection, float p_Beat, int p_LineIndex, int p_LineLayer) {
	NoteType = p_NoteType;
	CutDirection = p_CutDirection;
	Beat = p_Beat;
	LineIndex = p_LineIndex;
	LineLayer = p_LineLayer;
}