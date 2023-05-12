// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Saber.generated.h"

UCLASS()
class MEDIOCREMAPASSISTANT2_API AC_Saber : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Saber();

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly)
		USkeletalMeshComponent* SaberHandle;

	UPROPERTY(BlueprintReadOnly)
		USkeletalMeshComponent* SaberMesh;

	UPROPERTY(EditAnywhere)
		int m_LastNoteDirection;

	UPROPERTY(EditAnywhere)
		FVector m_LastNotePosition;

	UPROPERTY(EditAnywhere)
		FRotator m_LastNoteRotation;

	UFUNCTION()
		void OnTimelineChange();

public:	

	UFUNCTION(BlueprintCallable)
		void CutNote(int p_NoteCutDirection, FVector p_NotePosition, FRotator p_NoteRotation);
	
};
