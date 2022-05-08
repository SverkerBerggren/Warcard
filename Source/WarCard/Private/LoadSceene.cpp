// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadSceene.h"
#include "Kismet/GameplayStatics.h" 
// Sets default values for this component's properties
ULoadSceene::ULoadSceene()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULoadSceene::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULoadSceene::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("World'/Game/Levels/TestGrid.TestGrid'"), TRAVEL_Absolute);
	// ...
}

