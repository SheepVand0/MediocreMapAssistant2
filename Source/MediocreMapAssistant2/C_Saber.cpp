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

	SaberComponent = CreateDefaultSubobject<USceneComponent>("Saber Component");
	SaberComponent->SetupAttachment(GetRootComponent());

	SaberHandle = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Saber Handle"));
	SaberHandle->SetupAttachment(SaberComponent);

	SaberMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Saber Mesh"));
	SaberMesh->SetupAttachment(SaberHandle);

	m_SwingCurveComponent = CreateDefaultSubobject<UCurveFloat>(TEXT("Spray Curve"));

	m_SwingTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Spray Timeline"));
	m_SwingTimeline->AddInterpFloat(m_SwingCurveComponent, m_OnSwingTimelineCallback);
}

void AC_Saber::Swing(int p_NoteCutDirection, FVector p_NotePosition, float p_Time) {
	SetActorRotation(FQuat::MakeFromEuler(FVector(0, (p_NoteCutDirection * 45), 0)));
	float l_DelayBetweenNotes = p_Time - m_LastNoteTime;
	float l_SwingDuration = 0.1f;
	if (l_DelayBetweenNotes < 0.1f) {
		l_SwingDuration = l_DelayBetweenNotes;
	}
	m_SwingTimeline->SetTimelineLength(l_SwingDuration);
	m_SwingTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	m_SwingTimeline->SetPlaybackPosition(0.0f, false, false);
	FRichCurve l_SwingCurve;
	l_SwingCurve.AddKey(90, 0);
	l_SwingCurve.AddKey(-90, l_SwingDuration);
	m_SwingCurveComponent->FloatCurve = l_SwingCurve;
	m_SwingTimeline->PlayFromStart();
}

void AC_Saber::OnSwingTimelineCallback(float p_Value) {
	FRotator l_Rotator = SaberComponent->RelativeRotation;
	l_Rotator.Roll = p_Value;
	SaberComponent->SetRelativeRotation(l_Rotator);
}