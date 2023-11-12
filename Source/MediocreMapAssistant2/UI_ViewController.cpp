// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_ViewController.h"

AViewControllerAnimation::AViewControllerAnimation() {
	PrimaryActorTick.bCanEverTick = true;

}

void AViewControllerAnimation::BeginPlay() {
	Super::BeginPlay();

}

void AViewControllerAnimation::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("Delta time : %f"), UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()))
	if (m_IsPlaying == false) return;

	float l_AnimTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()) - m_StartTime;
	OnViewAnimationCallback(FMath::Clamp(l_AnimTime / m_Duration, 0.f, 1.f));
	if (l_AnimTime >= m_Duration) {
		OnViewAnimationFinished();
		m_IsPlaying = false;
	}
}

void AViewControllerAnimation::PlayAnimation() {
	m_StartTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	m_Duration = 0.25f;
	m_IsPlaying = true;
}

void AViewControllerAnimation::SetWidget(UUI_ViewController* p_Widget) {
	m_Widget = p_Widget;
}

void AViewControllerAnimation::OnViewAnimationCallback(float p_Value) {
	UE_LOG(LogTemp, Warning, TEXT("Animation Callback"))
	if (m_Widget) {
		m_Widget->OnViewAnimationCallback(p_Value);
	}
}

void AViewControllerAnimation::OnViewAnimationFinished() {
	if (m_Widget) {
		m_Widget->OnViewAnimationFinished();
	}
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

UUI_ViewController::UUI_ViewController() {

}

void UUI_ViewController::SetWidgets(TArray<UWidget*> p_Widget) {
	m_Widgets = p_Widget;
	for (int l_i = 0; l_i < m_Widgets.Num(); l_i++) {
		m_Widgets[l_i]->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (p_Widget.Num() > 0)
		SetWidget(0);
}

void UUI_ViewController::SetWidget(int p_Index) {
	if (m_SelectedWidget) {
		m_LastWidget = m_SelectedWidget;
	}

	if (!m_Widgets.IsValidIndex(p_Index)) return;

	m_SelectedWidget = m_Widgets[p_Index];
	m_SelectedWidgetIndex = p_Index;
	m_SelectedWidget->SetVisibility(ESlateVisibility::Visible);

	/*UVerticalBoxSlot* l_Slot = Cast<UVerticalBoxSlot>(AddChildToVerticalBox(m_SelectedWidget));

	l_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	l_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	l_Slot->Size.SizeRule = ESlateSizeRule::Fill;
	l_Slot->Size.Value = 1;
	l_Slot->Padding = FMargin(0, 0, 0, 0);*/
	

	if (m_AnimationActor == nullptr) {
		m_AnimationActor = AViewControllerAnimation::Create(GetWorld());
		m_AnimationActor->SetWidget(this);
	}
	m_AnimationActor->PlayAnimation();
}

void UUI_ViewController::OnViewAnimationCallback(float p_Value) {
	UE_LOG(LogTemp, Warning, TEXT("Time : %f"), p_Value);
	if (m_LastWidget) {
		m_LastWidget->SetRenderTranslation(FVector2D(p_Value * (-1 * m_Res.X) , 0));
		UE_LOG(LogTemp, Warning, TEXT("Doing for LastWidget"));
	}
	if (m_SelectedWidget) {
		m_SelectedWidget->SetRenderTranslation(FVector2D(m_Res.X - (p_Value * m_Res.X), 0));
		UE_LOG(LogTemp, Warning, TEXT("Doing for SelectedWidget"));
	}
}

void UUI_ViewController::OnViewAnimationFinished() {
	if (m_LastWidget)
		m_LastWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UUI_ViewController::SetRes(FVector2D p_Val) {
	m_Res = p_Val;
}

void UUI_ViewController::Hide() {
	if (m_SelectedWidget) {
		m_SelectedWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

int UUI_ViewController::GetSelectedWidgetIndex() {
	return m_SelectedWidgetIndex;
}