// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "Components/ScrollBox.h"


#include "UI_ViewController.generated.h"

UCLASS()
class MEDIOCREMAPASSISTANT2_API AViewControllerAnimation : public AActor {

	GENERATED_BODY()

	AViewControllerAnimation();

	UFUNCTION()
	void OnViewAnimationCallback(float p_Value);

	UFUNCTION()
	void OnViewAnimationFinished();

public:

	UFUNCTION()
	void SetWidget(UUI_ViewController* p_Widget);

	UFUNCTION()
	void PlayAnimation();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	static AViewControllerAnimation* Create(UWorld* p_World) {
		FActorSpawnParameters l_Param = FActorSpawnParameters();
		l_Param.bNoFail = true;
		return Cast<AViewControllerAnimation>(p_World->SpawnActor<AViewControllerAnimation>(l_Param));
	}

protected:

	float m_StartTime;
	float m_Duration;

	float m_Start = 0;
	float m_End = 1;

	bool m_IsPlaying = false;

	UPROPERTY()
	UUI_ViewController* m_Widget;

};

/**
 * 
 */
UCLASS()
class MEDIOCREMAPASSISTANT2_API UUI_ViewController : public UHorizontalBox
{
	GENERATED_BODY()
	
protected:

	UUI_ViewController();

	TArray<UWidget*> m_Widgets;

	UWidget* m_LastWidget;
	UWidget* m_SelectedWidget;

	FVector2D m_Res;

	int m_SelectedWidgetIndex = -1;

	virtual void OnWidgetSelected(int p_Value);
private:

	AViewControllerAnimation* m_AnimationActor;

public:
	
	UFUNCTION(BlueprintCallable)
	void SetWidgets(TArray<UWidget*> p_Widgets);

	UFUNCTION(BlueprintCallable)
	void SetWidget(int p_Index);

	UFUNCTION(BlueprintCallable)
	void SetRes(FVector2D p_Val);

	UFUNCTION(BlueprintCallable)
	void Hide();

	UFUNCTION(BlueprintPure)
	int GetSelectedWidgetIndex();

	void OnViewAnimationCallback(float p_Value);

	void OnViewAnimationFinished();

};
