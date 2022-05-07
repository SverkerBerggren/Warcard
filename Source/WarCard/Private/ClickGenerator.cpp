// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickGenerator.h"
#include "UnityInput.h"

#include "CameraManager.h"



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
	if (UnityInput::GetKeyPressed(EKeys::LeftMouseButton) || UnityInput::GetKeyPressed(EKeys::RightMouseButton))
	{
		ClickType Type = ClickType::LeftMouse;
		if (UnityInput::GetKeyPressed(EKeys::RightMouseButton))
		{
			Type = ClickType::RightMouse;
		}
		//UE_LOG(LogTemp, Warning, TEXT("LeftClickelick"));
		FVector2D MousePositon = UnityInput::GetMousePosition();
		UE_LOG(LogTemp, Warning, TEXT("Mouse position: %f %f"), MousePositon.X, MousePositon.Y);
		//TInlineComponentArray<CamereCo*> Cameras;
		//GetComponents<UCameraComponent>(/*out*/ Cameras);
		//
		//for (UCameraComponent* CameraComponent : Cameras)
		//{
		//	if (CameraComponent->bIsActive)
		//	{
		//		CameraComponent->GetCameraView(DeltaTime, OutResult);
		//		return;
		//	}
		//}
		
		//GetWorld()->GetFirstPlayerController()->PlayerCameraManager->getcamearvi

		// Set up parameters for getting the player viewport
		FVector PlayerViewPointLocation;
		FVector PlayerViewPointRotation;

		// Get player viewport and set these parameters
		//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		//	OUT PlayerViewPointLocation,
		//	OUT PlayerViewPointRotation
		//);
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation
		);
		if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::MouseScrollUp))
		{

		}
		if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::MouseScrollDown))
		{

		}
		// Parameter for how far out the the line trace reaches
		float Reach = 10000.f;
		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation * Reach;


		UE_LOG(LogTemp, Warning, TEXT("LineTraceBegin: %f %f %f"), PlayerViewPointLocation.X, PlayerViewPointLocation.Y, PlayerViewPointLocation.Z);
		UE_LOG(LogTemp, Warning, TEXT("LineTraceEnd: %f %f %f"), LineTraceEnd.X, LineTraceEnd.Y, LineTraceEnd.Z);

		// Set parameters to use line tracing
		FHitResult Hit;
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());  // false to ignore complex collisions and GetOwner() to ignore self

	// Raycast out to this distance
		GetWorld()->LineTraceSingleByObjectType(
			OUT Hit,
			PlayerViewPointLocation,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
			TraceParams
		);
		// See what if anything has been hit and return what
		AActor* ActorHit = Hit.GetActor();

		if (ActorHit) {
			UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit->GetName()));
			//ActorHit->Destroy();
			UClickable* ClickComponent = ActorHit->FindComponentByClass<UClickable>();
			if (ClickComponent)
			{
				ClickComponent->OnClick(Type);
			}
		}
	}
	// ...
}

