// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WCTile.h"
#include "WCUnitInfo.h"
#include "RuleEngine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileManager.generated.h"

//struct 

class UTileManager;
class AnimationHandler
{
public:
	UTileManager* AssociatedTileHandler = nullptr;
	virtual void Increment(float DeltaTime) = 0;
	virtual bool IsFinished() = 0;
	virtual ~AnimationHandler()
	{

	}
};

class Animation_Attack : public AnimationHandler
{
private:
	float m_ElapsedTime = 0;
	float m_TotalTime = 1.2;
	float m_AttackDuration = 0.5;
	float m_TakeDamageOffset = 0.7;
	float m_Amplitude = 100;
	FVector AttackerOriginalPosition;
	FVector DefenderOriginalPosition;
	AActor* AttackerObject = nullptr;
	AActor* DefenderObject = nullptr;
public:
	Animation_Attack(AActor* Attacker, AActor* Defender);
	void Increment(float DeltaTime) override;
	bool IsFinished() override;
};

enum class EventType
{
	Null,
	UnitDestroyed,

};

class Event
{
protected:
	EventType m_Type = EventType::Null;
public:
	virtual EventType GetType() const
	{
		return(m_Type);
	}
	virtual ~Event()
	{

	}
};

class Event_UnitDestroyed : public Event
{
public:
	Event_UnitDestroyed()
	{
		m_Type = EventType::UnitDestroyed;
	}
	WCE::UnitToken DestroyedUnit = 0;
	WCE::UnitPosition Position;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARCARD_API UTileManager : public UActorComponent,public GridReciever,public WCE::RuleEngineCallbackHandler
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

	size_t m_EventOffset = 0;
	TArray<TUniquePtr<Event>> m_EventStack = {};

	AnimationHandler* ActiveAnimation = nullptr;

	void UnitDestroyed(WCE::UnitToken DestroyedUnit) override
	{
		TUniquePtr<Event> EventData = TUniquePtr<Event>(new Event_UnitDestroyed());
		Event_UnitDestroyed* Data =(Event_UnitDestroyed*) EventData.Get();
		Data->DestroyedUnit = DestroyedUnit;
		for (size_t i = 0; i < Height; i++)
		{
			for (size_t j = 0; j < Width; j++)
			{
				if (m_PlacedUnits[i][j] == DestroyedUnit)
				{
					Data->Position.X = j;
					Data->Position.Y = i;
				}
			}
		}
		m_EventStack.Push(MoveTemp(EventData));
	}


	void DisplayAttackRange(WCE::UnitToken AssociatedUnit);
	void PlaceUnit(int PlayerIndex,int UnitIndex,FVector2D Position);
	void PlaceSwitch(WCE::UnitPosition SwitchPosition);
	void MoveUnit(WCE::UnitToken TokenToMove, WCE::UnitPosition NewPosition);
	void AttackUnit(WCE::UnitToken Attacker, WCE::UnitToken Defender);

	WCE::UnitToken SelectedUnit = 0;
	bool UnitSelected = false;

	//TArray<TArray<
	TArray<TArray<WCE::UnitToken>> m_PlacedUnits;
	TMap<WCE::UnitToken, AActor*> m_UnitActors;
	TArray<TArray<AActor*>> m_Grid;



	TArray<AActor*> m_HighlightTiles;

	WCE::RuleEngine m_RuleEngine;

	float m_TileWidth = 0;
	
	FVector2D m_GridStartPosition;

	void p_ClearSelectedTiles();

	void GridClick(ClickType Type,int X, int Y) override;
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
