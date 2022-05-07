// Fill out your copyright notice in the Description page of Project Settings.

#include "TileManager.h"
#include "UnityInput.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
//#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"

// Sets default values for this component's properties
UTileManager::UTileManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTileManager::BeginPlay()
{
	Super::BeginPlay();
	//return;
	double CurrentY = 0;
	double CurrentX = 0;
	double SpriteWidth = 0;
	m_Grid.Reserve(Height);
	m_PlacedUnits.Reserve(Height);
	for (int i = 0; i < Height; i++)
	{
		TArray<AActor*> NewRow;
		TArray<WCE::UnitToken> NewUnits;
		NewRow.Reserve(Width);
		NewUnits.Reserve(Width);
		for (int j = 0; j < Width; j++)
		{
			NewUnits.Add(0);
			FVector Position = { CurrentX,CurrentY,0 };
			FTransform NewTransform;
			NewTransform.SetLocation(Position);
			AActor* NewActor = GetWorld()->SpawnActor<AActor>(TileObject, NewTransform);
			UPaperSpriteComponent* SpriteComponent = NewActor->FindComponentByClass<UPaperSpriteComponent>();
			if(SpriteComponent)
			{
				SpriteWidth = SpriteComponent->GetSprite()->GetBakedTexture()->GetSizeX();
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("No sprite component for tiles"));
			}
			UWCTile* TileComponent = NewActor->FindComponentByClass<UWCTile>();
			if (TileComponent)
			{
				TileComponent->X = j;
				TileComponent->Y = i;
				TileComponent->AssociatedGrid = this;
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("No tile component for tiles"));
			}
			CurrentX += SpriteWidth;
			NewRow.Add(NewActor);
		}
		CurrentX = 0;
		CurrentY += SpriteWidth;
		m_Grid.Add(NewRow);
		m_PlacedUnits.Add(NewUnits);
	}
	m_RuleEngine = WCE::RuleEngine(Width, Height);
	m_GridStartPosition = FVector2D( 0,0 );
	m_TileWidth = SpriteWidth;

	PlaceUnit(1, 0, FVector2D(0, 0));
	PlaceUnit(1, 0, FVector2D(0, 1));
	PlaceUnit(1, 0, FVector2D(0, 2));
	PlaceUnit(2, 0, FVector2D(5, 0));
	PlaceUnit(2, 0, FVector2D(5, 1));
	PlaceUnit(2, 0, FVector2D(5, 2));
	// ...
	//Blue
}

void UTileManager::p_ClearSelectedTiles()
{
	for (size_t i = 0; i < m_HighlightTiles.Num(); i++)
	{
		m_HighlightTiles[i]->Destroy();
	}
	m_HighlightTiles.Empty();
}
void UTileManager::PlaceUnit(int PlayerIndex, int UnitIndex, FVector2D Position)
{
	if (UnitIndex < 0 || UnitIndex > Units.Num())
	{
		return;
	}
	if ((Position.X >= Width || Position.X < 0) || (Position.Y >= Height || Position.Y < 0))
	{
		return;
	}
	WCE::Unit UnitInfo;
	FVector ActorPosition = FVector(m_GridStartPosition.X+Position.X*m_TileWidth,m_GridStartPosition.Y+Position.Y* m_TileWidth,0);
	FTransform NewTransform;
	NewTransform.SetLocation(ActorPosition);
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(Units[UnitIndex], NewTransform);
	UWCUnitInfo* CurrentInfo = NewActor->FindComponentByClass<UWCUnitInfo>();
	if (CurrentInfo)
	{
		UnitInfo.CurrentHP = CurrentInfo->HP;
		UnitInfo.MovementSpeed = CurrentInfo->Movement;
		UnitInfo.Damage = CurrentInfo->Damage;
		UnitInfo.Type = CurrentInfo->UnitID;
		UnitInfo.Range = CurrentInfo->Range;
		UnitInfo.ActivationCost = CurrentInfo->ActivationCost;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No unit info in prefab"));
	}
	WCE::UnitPosition UnitPosition;
	UnitInfo.ControllerIndex = PlayerIndex;
	UnitPosition.X = Position.X;
	UnitPosition.Y = Position.Y;

	m_PlacedUnits[Position.Y][Position.X] = m_RuleEngine.RegisterUnit(MoveTemp(UnitInfo), UnitPosition);
	m_UnitActors.Add(m_PlacedUnits[Position.Y][Position.X], NewActor);
}
void UTileManager::MoveUnit(WCE::UnitToken TokenToMove, WCE::UnitPosition NewPosition)
{
	if (!m_UnitActors.Contains(TokenToMove))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid actor"));
		return;
	}
	WCE::RuleError Result = m_RuleEngine.MoveUnit(TokenToMove, NewPosition);
	if (Result != WCE::RuleError::Ok)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid move"));
		return;
	}
	AActor* AssociatedActor = m_UnitActors[TokenToMove];
	AssociatedActor->SetActorLocation(FVector(m_GridStartPosition.X+NewPosition.X*m_TileWidth, m_GridStartPosition.Y +NewPosition.Y*m_TileWidth, 0));
	WCE::UnitPosition Position = m_RuleEngine.GetUnitInfo(TokenToMove).Position;
	m_PlacedUnits[Position.Y][Position.X] = 0;
	m_PlacedUnits[NewPosition.Y][NewPosition.X] = TokenToMove;
}
Animation_Attack::Animation_Attack(AActor* Attacker, AActor* Defender)
{
	if (Attacker == nullptr || Defender == nullptr)
	{
		return;
	}
	AttackerObject = Attacker;
	AttackerOriginalPosition = AttackerObject->GetActorLocation();
	DefenderObject = Defender;
}
void Animation_Attack::Increment(float DeltaTime) 
{
	if (AttackerObject == nullptr || DefenderObject == nullptr)
	{
		return;
	}
	FVector NewPosition = AttackerOriginalPosition;
	NewPosition.X += FMath::Sin(m_ElapsedTime*m_ElapsedTime * 1000)* m_Amplitude;
	AttackerObject->SetActorLocation(NewPosition);
	m_ElapsedTime += DeltaTime;
}
bool Animation_Attack::IsFinished() 
{
	if (AttackerObject == nullptr || DefenderObject == nullptr)
	{
		return true;
	}
	bool ReturnValue = m_ElapsedTime >= m_TotalTime;
	if (ReturnValue)
	{
		AttackerObject->SetActorLocation(AttackerOriginalPosition);
	}
	return(ReturnValue);
}
void UTileManager::AttackUnit(WCE::UnitToken Attacker, WCE::UnitToken Defender)
{
	AActor* AttackerObject = nullptr;
	AActor* DefenderObject = nullptr;
	if (!(m_UnitActors.Contains(Attacker) && m_UnitActors.Contains(Defender)))
	{
		return;
	}
	AttackerObject = m_UnitActors[Attacker];
	DefenderObject = m_UnitActors[Defender];
	ActiveAnimation = new Animation_Attack(AttackerObject, DefenderObject);
}
void UTileManager::GridClick(ClickType Type,int X, int Y) 
{
	//UE_LOG(LogTemp, Warning, TEXT("Grid clickelick"));
	
	if (ActiveAnimation)
	{
		return;
	}



	if (m_HighlightTiles.Num() > 0)
	{
		p_ClearSelectedTiles();
	}
	UE_LOG(LogTemp, Warning, TEXT("Highlighting tile with unit %d"),m_PlacedUnits[Y][X]);


	if (UnitSelected == false)
	{
		if (m_PlacedUnits[Y][X] == 0)
		{
			FVector Position = FVector(m_GridStartPosition.X + X * m_TileWidth, m_GridStartPosition.Y + Y * m_TileWidth, 20);
			FTransform NewTransform;
			NewTransform.SetLocation(Position);
			AActor* NewActor = GetWorld()->SpawnActor<AActor>(SelectTile, NewTransform);
			m_HighlightTiles.Add(NewActor);
		}
		else
		{ 
			if (m_RuleEngine.GetActivePlayerIndex() != m_RuleEngine.GetUnitInfo(m_PlacedUnits[Y][X]).UnitData.ControllerIndex)
			{
				return;
			}
			UE_LOG(LogTemp, Warning, TEXT("Searcing available moves:"));
			TArray<WCE::UnitPosition> PossibleMoves = m_RuleEngine.PossibleMoves(m_PlacedUnits[Y][X]);
			for (auto& Move : PossibleMoves)
			{
				FVector Position = FVector(m_GridStartPosition.X + Move.X * m_TileWidth, m_GridStartPosition.Y + Move.Y * m_TileWidth, 20);
				FTransform NewTransform;
				NewTransform.SetLocation(Position);
				AActor* NewActor = GetWorld()->SpawnActor<AActor>(SelectTile, NewTransform);
				m_HighlightTiles.Add(NewActor);
			}
			UnitSelected = true;
			SelectedUnit = m_PlacedUnits[Y][X];
		}
	}
	else
	{
		TArray<WCE::UnitPosition> PossibleMoves = m_RuleEngine.PossibleMoves(SelectedUnit);
		if (PossibleMoves.Contains(WCE::UnitPosition{X,Y}))
		{
			MoveUnit(SelectedUnit, WCE::UnitPosition{ X,Y });
		}
		UnitSelected = false;
	}
}

// Called every frame
void UTileManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ActiveAnimation)
	{
		ActiveAnimation->Increment(DeltaTime);
		if (ActiveAnimation->IsFinished())
		{
			delete ActiveAnimation;
			ActiveAnimation = nullptr;
		}
		return;
	}
	//Test
	if (UnityInput::GetKeyDown(EKeys::SpaceBar))
	{
		AttackUnit(1, 2);
	}
	// ...
}

