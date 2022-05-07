// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickGenerator.generated.h"

UCLASS(Abstract)
class UClickable : public UActorComponent
{

	GENERATED_BODY()
public:
	virtual void OnClick()
	{
		
	};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UClickGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClickGenerator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
