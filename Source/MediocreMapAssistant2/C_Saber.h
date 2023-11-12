// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
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

	UPROPERTY(EditAnywhere)
		USceneComponent* SaberComponent;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SaberHandle;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SaberMesh;

protected:

	UFUNCTION()
		void OnSwingTimelineCallback(float p_Value);

	UPROPERTY()
		UTimelineComponent* m_SwingTimeline;

	FOnTimelineFloat m_OnSwingTimelineCallback;

	FOnTimelineEventStatic m_OnSwingTimelineFinished;

	UPROPERTY()
		int m_LastNoteDirection;

	UPROPERTY()
		FVector m_LastNotePosition;

	UPROPERTY()
		FRotator m_LastNoteRotation;

	UPROPERTY()
		float m_LastNoteTime;

	UPROPERTY()
		UCurveFloat* m_SwingCurveComponent;


public:	

	UFUNCTION(BlueprintCallable)
		void Swing(int p_NoteCutDirection, FVector p_NotePosition, float p_Time);


};
