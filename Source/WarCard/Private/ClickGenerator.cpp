// Fill out your copyright notice in the Description page of Project Settings.

#include "UnityInput.h"

#include "ClickGenerator.h"



// Sets default values for this component's properties
UClickGenerator::UClickGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClickGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//EKeys::
	//EKeys::
}


// Called every frame
void UClickGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (UnityInput::GetKeyDown(EKeys::LeftMouseButton))
	{
		//UE_LOG(LogTemp, Warning, TEXT("LeftClickelick"));
		FVector2D MousePositon = UnityInput::GetMousePosition();
		UE_LOG(LogTemp, Warning, TEXT("Mouse position: %f %f"), MousePositon.X, MousePositon.Y);
	}
	// ...
}

