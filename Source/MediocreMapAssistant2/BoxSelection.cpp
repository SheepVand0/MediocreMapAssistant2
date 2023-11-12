// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxSelection.h"


// Sets default values
ABoxSelectionManager::ABoxSelectionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoxSelectionManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxSelectionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* l_PlayerController = UGameplayStatics::GetPlayerController(Cast<UObject>(GetWorld()), 0);
	FVector l_MousePosition;
	FVector l_MouseDirection;
	l_PlayerController->DeprojectMousePositionToWorld(l_MousePosition, l_MouseDirection);

}


