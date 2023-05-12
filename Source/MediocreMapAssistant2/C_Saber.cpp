// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Saber.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AC_Saber::AC_Saber()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(Root);

	SaberHandle = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Saber Handle"));
	SaberHandle->SetupAttachment(GetRootComponent());

	SaberMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Saber Mesh"));
	SaberMesh->SetupAttachment(SaberHandle);
}

void AC_Saber::CutNote(int p_NoteCutDirection, FVector p_NotePosition, FRotator p_NoteRotation) {

	FVector l_SaberLocation = GetActorLocation();
	FVector l_NotePosition = p_NotePosition;

	FRotator l_NoteRotation = p_NoteRotation;

	int l_NoteDirection = p_NoteCutDirection;

	FRotator l_LookRotation = UKismetMathLibrary::FindLookAtRotation(l_SaberLocation, l_NotePosition);

	float l_Z = l_LookRotation.Yaw;

	if (l_Z < 0) l_Z += 180;

	bool l_IsReset = (m_LastNoteRotation.Pitch < l_NoteRotation.Pitch + 45 && m_LastNoteRotation.Pitch > l_NoteRotation.Pitch - 45);
	if (m_LastNoteDirection != 1 && l_IsReset)
		//OnPopupRequieredEvent.ExecuteIfBound(FString("Reset"));

	SetActorRotation(FRotator::MakeFromEuler(FVector(GetActorRotation().Roll, GetActorRotation().Pitch, l_Z)));

	FTimeline l_TimeLine = FTimeline{};
	l_TimeLine.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

	UCurveFloat* l_Curve = CreateDefaultSubobject<UCurveFloat>(TEXT("Curve"));
	l_Curve->FloatCurve.AddKey(0.0f, 0.0f);
	l_Curve->FloatCurve.AddKey(0.16f, 1.0f);

	l_TimeLine.SetFloatCurve(l_Curve, TEXT("Curve"));

	FOnTimelineEvent l_TimeLineEvent;
	l_TimeLineEvent.BindUFunction(this, "OnTimelineChange");

	l_TimeLine.SetTimelinePostUpdateFunc(l_TimeLineEvent);
}

void AC_Saber::OnTimelineChange() {

}