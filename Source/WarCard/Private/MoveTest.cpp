// Fill out your copyright notice in the Description page of Project Settings.
//#include "APlayerController.h"

#include "UnityInput.h"
#include "CameraManager.h"
#include "MoveTest.h"


// Sets default values for this component's properties
UMoveTest::UMoveTest()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveTest::BeginPlay()
{
	Super::BeginPlay();
	
	//FVector3d ControllerLocation;
	//ControllerLocation.X = 1000;
	//ControllerLocation.Y = 1000;
	//ControllerLocation.Z = 1000;
	//m_PlayerInput = GetWorld()->SpawnActor<APlayerController>(ControllerLocation,GetOwner<AActor>()->GetActorRotation());

	// ...
	
}


// Called every frame
void UMoveTest::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FTransform NewTransform = GetOwner<AActor>()->GetTransform();
	FVector3d NewPosition = NewTransform.GetTranslation();
	//NewPosition.X += 4;
	//if(GetWorld()->GetFirstPlayerController()->IsInputKeyDown("D") || GetWorld()->GetFirstPlayerController()->IsInputKeyDown("d"))
	//{
	//	NewPosition.X += 4;
	//	UE_LOG(LogTemp, Warning, TEXT("ShouldDoStuff"));
	//}
	if (UnityInput::GetKeyDown(UnityKeyCode::D))
	{
		NewPosition.X += MoveSpeed * (UCameraManager::GetActiveCamera()->OrthoWidth)*DeltaTime;
	}
	if (UnityInput::GetKeyDown(UnityKeyCode::A))
	{
		NewPosition.X -= MoveSpeed * (UCameraManager::GetActiveCamera()->OrthoWidth) * DeltaTime;
	}
	if (UnityInput::GetKeyDown(UnityKeyCode::S))
	{
		NewPosition.Y += MoveSpeed * (UCameraManager::GetActiveCamera()->OrthoWidth) * DeltaTime;
	}
	if (UnityInput::GetKeyDown(UnityKeyCode::W))
	{
		NewPosition.Y -= MoveSpeed * (UCameraManager::GetActiveCamera()->OrthoWidth) * DeltaTime;
	}
	if (UnityInput::GetKeyDown(EKeys::RightMouseButton))
	{
		FVector2D ViewportSize;
		GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
		FVector2D Delta =  UnityInput::GetMouseDrag();

		float DeltaX = -(Delta.X /ViewportSize.X)*UCameraManager::GetActiveCamera()->OrthoWidth *100;
		//UE_LOG(LogTemp, Warning, TEXT("Delta X %f ViemportSizeX %f OrthoWidth %f Result %f"), Delta.X, ViewportSize.X, UCameraManager::GetActiveCamera()->OrthoWidth,DeltaX);
		float DeltaY = (Delta.Y/ViewportSize.Y) * UCameraManager::GetActiveCamera()->OrthoWidth/UCameraManager::GetActiveCamera()->AspectRatio * 100;
		

		NewPosition.X += DeltaX;
		NewPosition.Y += DeltaY;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::MouseScrollUp) || GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::MouseScrollUp))
	{
		UCameraManager::GetActiveCamera()->SetOrthoWidth(UCameraManager::GetActiveCamera()->OrthoWidth - ScrollSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Scrolling"));
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::MouseScrollDown) || GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::MouseScrollDown))
	{
		UCameraManager::GetActiveCamera()->SetOrthoWidth(UCameraManager::GetActiveCamera()->OrthoWidth + ScrollSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Scrolling"));
	}
	//GetWorld()->GetFirstPlayerController().mousedelta
	//	UE_LOG(LogTemp, Warning, TEXT("InTick"));
	NewTransform.SetComponents(NewTransform.GetRotation(),NewPosition, NewTransform.GetScale3D());
	bool Result = GetOwner<AActor>()->SetActorTransform(NewTransform);


	//UE_LOG(LogTemp, Warning, TEXT("Result: %d"),Result);
	// ...
}

