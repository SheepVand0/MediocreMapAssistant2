// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_TabControl.h"

FTabData::FTabData() {

}

FTabData::FTabData(FString p_TabName, UButton* p_Button) {
	TabName = p_TabName;
	TabButtonWidget = p_Button;
}

/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void UTabButton::SetTabButtonWidget(UButton* p_Button) {
	if (!p_Button) return;

	if (m_Button) {
		m_Button->OnClicked.RemoveAll(this);
	}

	m_Button = p_Button;
	m_Button->OnClicked.AddDynamic(this, &UTabButton::OnButtonClicked);
}

void UTabButton::SetTabIndex(int p_TabIndex) {
	m_TabIndex = p_TabIndex;
}

void UTabButton::SetParentTabControl(UUI_TabControl* p_Tab) {
	if (!p_Tab) return;
	m_TabControl = p_Tab;
}

void UTabButton::OnButtonClicked() {
	if (!m_TabControl && m_TabIndex != -1) return;

	m_TabControl->SetWidget(m_TabIndex);
}

/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

UUI_TabControl::UUI_TabControl() {
	
}

void UUI_TabControl::SetTabs(TArray<FTabData> p_Tabs) {
	m_Tabs = p_Tabs;

	UE_LOG(LogTemp, Warning, TEXT("Doing 1"));

	if (p_Tabs.Num() == 0) return;

	UE_LOG(LogTemp, Warning, TEXT("Doing 2"));

	for (int l_i = 0; l_i < p_Tabs.Num(); l_i++) {
		UTabButton* l_Button = NewObject<UTabButton>(this, *FName::NameToDisplayString(FString("TabButton ") + FString::SanitizeFloat(l_i, 0), false));
		if (l_Button == nullptr) continue;

		//l_Slot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		l_Button->SetTabButtonWidget(p_Tabs[l_i].TabButtonWidget);
		l_Button->SetParentTabControl(this);
		l_Button->SetTabIndex(l_i);
		l_Button->OnTabButtonClickedEvent.AddDynamic(this, &UUI_TabControl::OnTabButtonClicked);
		//m_Buttons.Add(l_Button);
		UE_LOG(LogTemp, Warning, TEXT("Doing 3"));
	}
}

void UUI_TabControl::OnTabButtonClicked(int p_Index) {
	SetWidget(p_Index);
}

void UUI_TabControl::OnWidgetSelected(int p_SelectedIndex) {

}