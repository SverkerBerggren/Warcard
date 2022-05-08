// Fill out your copyright notice in the Description page of Project Settings.

#include "TileManager.h"
#include "UnityInput.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

#include "UiTest.h"
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
	m_RuleEngine.SetCallbackHandler(this);
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
				//SpriteComponent->SetSprite();
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
	if (UUiTest::GetHud())
	{
		//UUiTest::GetHud()->SetVisibility(ESlateVisibility::Hidden);
		UUiTest::GetHud()->SetButtonCallback(this);
	}
	m_RuleEngine = WCE::RuleEngine(Width, Height);
	m_GridStartPosition = FVector2D( 0,0 );
	m_TileWidth = SpriteWidth;
	m_RuleEngine.SetCallbackHandler(this);
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
		UnitInfo.Type = CurrentInfo->UnitID;
		m_UnitTypeIndexes.Add(UnitInfo.Type, UnitIndex);
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
	UPaperSpriteComponent* SpriteComponent = NewActor->FindComponentByClass<UPaperSpriteComponent>();
	if (SpriteComponent)
	{
		if (PlayerIndex == 1)
		{
			if (CurrentInfo->IdleSprite1)
			{
				//SpriteComponent->SetWorldRotation()
				SpriteComponent->AddLocalRotation(FRotator(0,180,0));
				SpriteComponent->SetSprite(CurrentInfo->IdleSprite1);
			}
		}
		if (PlayerIndex == 2)
		{
			if (CurrentInfo->IdleSprite2)
			{
				SpriteComponent->SetSprite(CurrentInfo->IdleSprite2);
			}
		}
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
Animation_Attack::Animation_Attack(AActor* Attacker, AActor* Defender,int AttackPlayer)
{
	if (Attacker == nullptr || Defender == nullptr)
	{
		return;
	}
	m_AttackPlayer = AttackPlayer;
	AttackerObject = Attacker;
	AttackerOriginalPosition = AttackerObject->GetActorLocation();
	DefenderOriginalPosition = Defender->GetActorLocation();
	DefenderObject = Defender;
}
void Animation_Attack::Increment(float DeltaTime) 
{
	if (AttackerObject == nullptr || DefenderObject == nullptr)
	{
		return;
	}
	AttackerObject->SetActorLocation(AttackerOriginalPosition);
	DefenderObject->SetActorLocation(DefenderOriginalPosition);
	if (m_ElapsedTime < m_AttackDuration)
	{
		FVector NewPosition = AttackerOriginalPosition;
		NewPosition.X += FMath::Sin(m_ElapsedTime * m_ElapsedTime * 40) * m_Amplitude;
		AttackerObject->SetActorLocation(NewPosition);
	}
	else if(m_ElapsedTime >= m_TakeDamageOffset)
	{
		FVector NewPosition = DefenderOriginalPosition;
		NewPosition.X += FMath::Sin(m_ElapsedTime * m_ElapsedTime * 1000) * m_Amplitude;
		DefenderObject->SetActorLocation(NewPosition);
		UPaperSpriteComponent* SpriteComponent = DefenderObject->FindComponentByClass<UPaperSpriteComponent>();
		if (SpriteComponent)
		{
			UWCUnitInfo* UnitInfo = DefenderObject->FindComponentByClass<UWCUnitInfo>();
			if (UnitInfo)
			{
				UPaperSprite* SpriteToSet = nullptr;
				if (m_AttackPlayer == 1)
				{
					SpriteToSet = UnitInfo->DamageSprite2;
				}
				else
				{
					SpriteToSet = UnitInfo->DamageSprite1;
				}
				if (DefenderFirstSprite == nullptr)
				{
					DefenderFirstSprite = SpriteComponent->GetSprite();
				}
				if (SpriteToSet)
				{
					SpriteComponent->SetSprite(SpriteToSet);
				}

			}
		}
	}
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
		DefenderObject->SetActorLocation(DefenderOriginalPosition);
		AttackerObject->SetActorLocation(AttackerOriginalPosition);
		UPaperSpriteComponent* SpriteComponent = DefenderObject->FindComponentByClass<UPaperSpriteComponent>();
		if (SpriteComponent)
		{
			if (DefenderFirstSprite)
			{
				SpriteComponent->SetSprite(DefenderFirstSprite);
			}
		}
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
	ActiveAnimation = new Animation_Attack(AttackerObject, DefenderObject,m_RuleEngine.GetUnitInfo(Attacker).UnitData.ControllerIndex);
	m_RuleEngine.Attack(Attacker, Defender);
}
void UTileManager::OnClick(ButtonType button)
{
	LastButtonType = button;
	UE_LOG(LogTemp, Warning, TEXT("On Click fired: %d"),LastButtonType);
	if (UnitSelected)
	{
		if (m_HighlightTiles.Num() > 0)
		{
			p_ClearSelectedTiles();
		}
		if (LastButtonType == ButtonType::Move)
		{
			if (m_RuleEngine.GetActivePlayerIndex() != m_RuleEngine.GetUnitInfo(SelectedUnit).UnitData.ControllerIndex)
			{
				return;
			}
			UE_LOG(LogTemp, Warning, TEXT("Searcing available moves:"));
			TArray<WCE::UnitPosition> PossibleMoves = m_RuleEngine.PossibleMoves(SelectedUnit);
			for (auto& Move : PossibleMoves)
			{
				FVector Position = FVector(m_GridStartPosition.X + Move.X * m_TileWidth, m_GridStartPosition.Y + Move.Y * m_TileWidth, 20);
				FTransform NewTransform;
				NewTransform.SetLocation(Position);
				AActor* NewActor = GetWorld()->SpawnActor<AActor>(SelectTile, NewTransform);
				m_HighlightTiles.Add(NewActor);
			}
		}
		if (LastButtonType == ButtonType::Attack)
		{
			if (m_RuleEngine.GetActivePlayerIndex() != m_RuleEngine.GetUnitInfo(SelectedUnit).UnitData.ControllerIndex)
			{
				return;
			}
			WCE::UnitInfo const& Info = m_RuleEngine.GetUnitInfo(SelectedUnit);
			for (int i = 0; i < Info.UnitData.Range+1; i++)
			{
				int CurrentX = Info.Position.X - i;
				for (int j = (-Info.UnitData.Range+i); j <= (Info.UnitData.Range-i); j++)
				{
					int CurrentY = Info.Position.Y+j;
					if (CurrentY < 0 || CurrentY >= Height)
					{
						continue;
					}
					if (CurrentX < 0 || CurrentX >= Width)
					{
						continue;
					}
					FVector Position = FVector(CurrentX * m_TileWidth, CurrentY *m_TileWidth, 20);
					FTransform NewTransform;
					NewTransform.SetLocation(Position);
					AActor* NewActor = GetWorld()->SpawnActor<AActor>(EnemyTile, NewTransform);
					m_HighlightTiles.Add(NewActor);
				}
				if (i != 0)
				{
					CurrentX = Info.Position.X + i;
					for (int j = (-Info.UnitData.Range + i); j <= (Info.UnitData.Range - i); j++)
					{
						int CurrentY = Info.Position.Y + j;
						if (CurrentY < 0 || CurrentY >= Height)
						{
							continue;
						}
						if (CurrentX < 0 || CurrentX >= Width)
						{
							continue;
						}
						FVector Position = FVector(CurrentX * m_TileWidth, CurrentY * m_TileWidth, 20);
						FTransform NewTransform;
						NewTransform.SetLocation(Position);
						AActor* NewActor = GetWorld()->SpawnActor<AActor>(EnemyTile, NewTransform);
						m_HighlightTiles.Add(NewActor);
					}
				}
			}
		}
	}
	if (LastButtonType == ButtonType::ChangeTurn)
	{
		ResetSelect();
		p_ClearSelectedTiles();
		m_RuleEngine.PassTurn();
		UUiTest::GetHud()->SetInitiativ(m_RuleEngine.GetActivePlayerInitiative());
		UUiTest::GetHud()->SetActivePlayer(m_RuleEngine.GetActivePlayerIndex());
	}
}


void UTileManager::ResetSelect()
{
	SelectedUnit = 0;
	UnitSelected = 0;
	LastButtonType = ButtonType::Null;
	UUiTest::GetHud()->SetBottomHud(ESlateVisibility::Hidden);
	UUiTest::GetHud()->SetCardVisiblity(ESlateVisibility::Hidden);
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
	if (UnitSelected == false)
	{
		FVector Position = FVector(m_GridStartPosition.X + X * m_TileWidth, m_GridStartPosition.Y + Y * m_TileWidth, 20);
		FTransform NewTransform;
		NewTransform.SetLocation(Position);
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(SelectTile, NewTransform);
		m_HighlightTiles.Add(NewActor);
		if (m_PlacedUnits[Y][X] == 0)
		{
			ResetSelect();
		}
		else
		{ 
			WCE::UnitInfo const& Info = m_RuleEngine.GetUnitInfo(m_PlacedUnits[Y][X]);
			if (m_UnitTypeIndexes.Contains(Info.UnitData.Type))
			{
				int Index = m_UnitTypeIndexes[Info.UnitData.Type];
				AActor* InfoActor = GetWorld()->SpawnActor<AActor>(Units[Index], NewTransform);
				UWCUnitInfo* CurrentInfo = InfoActor->FindComponentByClass<UWCUnitInfo>();
				if (CurrentInfo)
				{
					CurrentInfo->HP = Info.UnitData.CurrentHP;
					CurrentInfo->Damage = Info.UnitData.Damage;
					CurrentInfo->Range = Info.UnitData.Range;
					CurrentInfo->Movement = Info.UnitData.MovementSpeed;
					CurrentInfo->ActivationCost = Info.UnitData.ActivationCost;
					UUiTest::GetHud()->CreateUnitCard(CurrentInfo);
				}
				UE_LOG(LogTemp, Warning, TEXT("Creating new card"));
				InfoActor->Destroy();
			}
			UUiTest::GetHud()->SetCardVisiblity(ESlateVisibility::Visible);
			bool AffordActivation = (Info.UnitData.Flags & uint64_t(WCE::UnitFlags::Activated)) || Info.UnitData.ActivationCost <= m_RuleEngine.GetActivePlayerInitiative();
			if (Info.UnitData.Flags & uint64_t(WCE::UnitFlags::Moved) || !AffordActivation)
			{
				UUiTest::GetHud()->SetBottomButton(ButtonType::Move, 0);
			}
			else
			{
				UUiTest::GetHud()->SetBottomButton(ButtonType::Move, 1);
			}
			if (Info.UnitData.Flags & uint64_t(WCE::UnitFlags::Attacked) || !AffordActivation)
			{
				UUiTest::GetHud()->SetBottomButton(ButtonType::Attack, 0);
			}
			else
			{
				UUiTest::GetHud()->SetBottomButton(ButtonType::Attack, 1);
			}
			UUiTest::GetHud()->SetBottomButton(ButtonType::Ability, 0);
			if (m_RuleEngine.GetActivePlayerIndex() != m_RuleEngine.GetUnitInfo(m_PlacedUnits[Y][X]).UnitData.ControllerIndex)
			{
				return;
			}
			UUiTest::GetHud()->SetBottomHud(ESlateVisibility::Visible);
			UnitSelected = true;
			SelectedUnit = m_PlacedUnits[Y][X];
		}
		UE_LOG(LogTemp, Warning, TEXT("Selecting unit %d"), m_PlacedUnits[Y][X]);
	}
	else
	{
		if (m_RuleEngine.GetActivePlayerIndex() == m_RuleEngine.GetUnitInfo(SelectedUnit).UnitData.ControllerIndex)
		{
			if (LastButtonType == ButtonType::Move)
			{
				auto AvailableMoves = m_RuleEngine.PossibleMoves(SelectedUnit);
				WCE::UnitPosition NewLocation{ X,Y };
				if (AvailableMoves.Contains(NewLocation))
				{
					MoveUnit(SelectedUnit, NewLocation);
					UUiTest::GetHud()->SetInitiativ(m_RuleEngine.GetActivePlayerInitiative());
				}
			}
			else if (LastButtonType == ButtonType::Attack)
			{
				if (m_PlacedUnits[Y][X] != 0)
				{
					WCE::UnitInfo const& SelectedInfo = m_RuleEngine.GetUnitInfo(SelectedUnit);
					WCE::UnitInfo const& Info = m_RuleEngine.GetUnitInfo(m_PlacedUnits[Y][X]);
					if (Info.UnitData.ControllerIndex != SelectedInfo.UnitData.ControllerIndex)
					{
						if (abs(SelectedInfo.Position.X - Info.Position.X) + abs(SelectedInfo.Position.Y - Info.Position.Y) <= SelectedInfo.UnitData.Range)
						{
							AttackUnit(SelectedUnit, m_PlacedUnits[Y][X]);
							UUiTest::GetHud()->SetInitiativ(m_RuleEngine.GetActivePlayerInitiative());
						}
					}
				}
			}
		}
		ResetSelect();
	}
}

// Called every frame
void UTileManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!RuntimeInitialized)
	{
		if (UUiTest::GetHud())
		{
			UUiTest::GetHud()->SetBottomHud(ESlateVisibility::Hidden);
			UUiTest::GetHud()->SetCardVisiblity(ESlateVisibility::Hidden);
			//UUiTest::GetHud()->UpdatePlayerScore(1,10);
			//UUiTest::GetHud()->UpdatePlayerScore(2,10);
			UUiTest::GetHud()->SetButtonCallback(this);
		}
		RuntimeInitialized = true;
	}
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
	for (int i = m_EventOffset; i < m_EventStack.Num(); i++)
	{
		if (m_EventStack[i]->GetType() == EventType::UnitDestroyed)
		{
			Event_UnitDestroyed const& DestroyEvent =static_cast<Event_UnitDestroyed const&>(*m_EventStack[i].Get());
			if (m_UnitActors.Contains(DestroyEvent.DestroyedUnit))
			{
				WCE::UnitToken DestroyedUnit = DestroyEvent.DestroyedUnit;
				m_UnitActors[DestroyedUnit]->Destroy();
				m_UnitActors.Remove(DestroyedUnit);
				m_PlacedUnits[DestroyEvent.Position.Y][DestroyEvent.Position.X] = 0;
			}
		}
	}
	m_EventStack.Empty();
	//Test
	//if (UnityInput::GetKeyDown(EKeys::SpaceBar))
	//{
	//	AttackUnit(1, 4);
	//}
	// ...
}

