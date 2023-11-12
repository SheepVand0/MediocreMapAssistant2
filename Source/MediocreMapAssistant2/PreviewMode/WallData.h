// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WallData.generated.h"

UENUM()
enum class EWallType : uint8 {
	Full = 0,
	Duck = 1
};

/**
 * 
 */
UCLASS()
class MEDIOCREMAPASSISTANT2_API UWallData : public UObject
{

	GENERATED_BODY()

public:

	UWallData();
	~UWallData();

	UPROPERTY(BlueprintReadWrite)
		float Beat;

	UPROPERTY(BlueprintReadWrite)
		int LineIndex;

	UPROPERTY(BlueprintReadWrite)
		EWallType WallType;

	UPROPERTY(BlueprintReadWrite)
		float Duration;

	UPROPERTY(BlueprintReadWrite)
		int Width;
};
