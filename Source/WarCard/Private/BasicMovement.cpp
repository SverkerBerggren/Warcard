// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFrameWork/PlayerController.h"

#include "BasicMovement.h"


// Sets default values for this component's properties
UBasicMovement::UBasicMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBasicMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBasicMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

