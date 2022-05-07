// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WCTile.h"
#include "RuleEngine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileManager.generated.h"

//struct 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UTileManager : public UActorComponent,public GridReciever
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TileObject;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SelectTile;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> FriendlyTile;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EnemyTile;

	UPROPERTY(EditAnywhere)
	int Height = 20;
	UPROPERTY(EditAnywhere)
	int Width = 20;

	UPROPERTY(EditAnywhere);
	TArray<TSubclassOf<AActor>> Units;


	//TArray<TArray<

	TArray<TArray<AActor*>> m_Grid;
	TArray<AActor*> m_HighlightTiles;

	WCE::RuleEngine m_RuleEngine;

	float m_TileWidth = 0;
	
	FVector2D m_GridStartPosition;

	void p_ClearSelectedTiles();

	void GridClick(int X, int Y) override;
	//UPROPERTY(EditAnywhere)
	//A
	//AActor
	

	// Sets default values for this component's properties
	UTileManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
