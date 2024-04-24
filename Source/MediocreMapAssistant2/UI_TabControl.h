// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_ViewController.h"
#include "Components/Button.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "UObject/UObjectGlobals.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "UI_TabControl.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabButtonClicked, int, p_TabIndex);

USTRUCT(BlueprintType)
struct FTabData {

	GENERATED_BODY()

public:

	FTabData();

	FTabData(FString p_TabName, UButton* p_TabWidget);

	UPROPERTY(BlueprintReadWrite)
	FString TabName;

	UPROPERTY(BlueprintReadWrite)
	UButton* TabButtonWidget;

};

UCLASS()
class MEDIOCREMAPASSISTANT2_API UTabButton : public UObject {

	GENERATED_BODY()

protected:

	UPROPERTY()
	int m_TabIndex = -1;

	UPROPERTY()
	UUI_TabControl* m_TabControl;
	

	UFUNCTION()
	void OnButtonClicked();

	UPROPERTY()
	UButton* m_Button;

public:

	UFUNCTION(BlueprintCallable)
	void SetTabIndex(int p_Index);
	
	UFUNCTION(BlueprintCallable)
	void SetParentTabControl(UUI_TabControl* p_TabControl);

	UFUNCTION(BlueprintCallable)
	void SetTabButtonWidget(UButton* p_Button);

	UPROPERTY(BlueprintAssignable)
	FOnTabButtonClicked OnTabButtonClickedEvent;
};

/**
 * 
 */
UCLASS()
class MEDIOCREMAPASSISTANT2_API UUI_TabControl : public UUI_ViewController
{
	GENERATED_BODY()
	
protected:

	TArray<FTabData> m_Tabs;
	TArray<UTabButton*> m_Buttons;

	UUI_TabControl();

	virtual void OnWidgetSelected(int p_Index) override;

	UFUNCTION()
	void OnTabButtonClicked(int p_Index);

public:

	UFUNCTION(BlueprintCallable)
	void SetTabs(TArray<FTabData> p_Tabs);

};
