// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

UCameraComponent* G_GlobalCameraComponent = nullptr;

// Sets default values for this component's properties
UCameraManager::UCameraManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraManager::BeginPlay()
{
	Super::BeginPlay();
	G_GlobalCameraComponent = this->GetOwner<AActor>()->FindComponentByClass<UCameraComponent>();
	// ...
	
}

UCameraComponent* UCameraManager::GetActiveCamera()
{
	if (!G_GlobalCameraComponent)
	{
		UE_LOG(LogTemp, Fatal, TEXT("No camera registred"));
	}
	return(G_GlobalCameraComponent);
}

// Called every frame
void UCameraManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	G_GlobalCameraComponent = this->GetOwner<AActor>()->FindComponentByClass<UCameraComponent>();
	// ...
}

