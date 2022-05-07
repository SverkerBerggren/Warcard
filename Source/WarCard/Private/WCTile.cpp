// Fill out your copyright notice in the Description page of Project Settings.


#include "WCTile.h"

// Sets default values for this component's properties
UWCTile::UWCTile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UWCTile::OnClick()
{
	if (AssociatedGrid)
	{
		AssociatedGrid->GridClick(X, Y);
	}
}

// Called when the game starts
void UWCTile::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWCTile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

