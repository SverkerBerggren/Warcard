// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ClickGenerator.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WCTile.generated.h"


class GridReciever
{
public:
	virtual void GridClick(ClickType Type,int X, int Y) = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UWCTile : public UClickable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWCTile();

	GridReciever* AssociatedGrid = nullptr;
	int X = 0;
	int Y = 0;

	void OnClick(ClickType) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
