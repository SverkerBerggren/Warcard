// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnityInput.generated.h"


enum class UnityKeyCode
{
	Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M, Space, Enter
};

class UnityInput
{
public:
	static bool GetKeyDown(UnityKeyCode CodeToCheck);
	static bool GetKeyUp(UnityKeyCode CodeToCheck);
	static bool GetKeyPressed(UnityKeyCode CodeToCheck);

	static bool GetKeyDown(FKey KeyToCheck);
	static bool GetKeyUp(FKey KeyToCheck);
	static bool GetKeyPressed(FKey KeyToCheck);

	static FVector2D GetMousePosition();

	void GetMouseDrag(double& OutX, double& OutY);
};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UUnityInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnityInput();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
