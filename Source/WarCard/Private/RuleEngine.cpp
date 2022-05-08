#include "RuleEngine.h"


namespace WCE
{
	//Observers
	UnitPosition RuleEngine::GetUnitPosition(UnitToken AssociatedUnit) const
	{
		UnitPosition ReturnValue;

		return(ReturnValue);
	}
	struct MoveDirection
	{
		int X = 0;
		int Y = 0;
	};
	void RuleEngine::i_RecursiveTraversal(UnitInfo const& Info,UnitPosition CurrentPosition,int PossibleMoves,TArray<UnitPosition>& OutResult) const
	{
		UE_LOG(LogTemp, Warning, TEXT("Traversing: Original position %d %d"),CurrentPosition.X,CurrentPosition.Y);
		if (PossibleMoves <= 0)
		{
			return;
		}
		TArray<MoveDirection> MoveDirections = { MoveDirection{1,0},MoveDirection{0,1},MoveDirection{-1,0},MoveDirection{0,-1} };
		for (auto& Direction : MoveDirections)
		{
			UnitPosition NewPosition = UnitPosition{ CurrentPosition.X + Direction.X, CurrentPosition.Y + Direction.Y };
			UE_LOG(LogTemp, Warning, TEXT("New position %d %d"), NewPosition.X, NewPosition.Y);
			if (NewPosition.X < 0 || NewPosition.X >= m_GridWidth)
			{
				continue;
			}
			if (NewPosition.Y < 0 || NewPosition.Y >= m_GridHeight)
			{
				continue;
			}
			if (m_Tiles[NewPosition.Y][NewPosition.X].StandingUnit != 0)
			{
				if (m_UnitInfos[m_Tiles[NewPosition.Y][NewPosition.X].StandingUnit].UnitData.ControllerIndex != Info.UnitData.ControllerIndex)
				{
					continue;
				}
				i_RecursiveTraversal(Info, NewPosition, PossibleMoves - 1, OutResult);
				continue;
			}
			UE_LOG(LogTemp, Warning, TEXT("Added position %d %d"), NewPosition.X, NewPosition.Y);
			OutResult.Add(NewPosition);
			i_RecursiveTraversal(Info, NewPosition, PossibleMoves - 1, OutResult);
		}
	}
	TArray<UnitPosition> RuleEngine::PossibleMoves(UnitToken AssociatedUnit) const
	{
		TArray<UnitPosition> ReturnValue;
		if (!m_UnitInfos.Contains(AssociatedUnit))
		{
			return ReturnValue;
		}
		UnitInfo const& Info = m_UnitInfos[AssociatedUnit];
		TArray<UnitPosition> Result;
		i_RecursiveTraversal(Info, Info.Position, Info.UnitData.MovementSpeed, Result);
		Result.Sort();
		for (int i = 0; i < Result.Num(); i++)
		{
			if (i + 1 < Result.Num() && (Result[i].X == Result[i + 1].X && Result[i].Y == Result[i+1].Y))
			{
				continue;
			}
			ReturnValue.Add(Result[i]);
		}
		return(ReturnValue);
	}
	UnitInfo const& RuleEngine::GetUnitInfo(UnitToken AssociatedUnit) const
	{
		if (!m_UnitInfos.Contains(AssociatedUnit))
		{
			throw std::exception();
		}
		return(m_UnitInfos[AssociatedUnit]);
	}
	UnitToken RuleEngine::RegisterUnit(Unit InfoToInsert, UnitPosition Position)
	{
		UnitToken ReturnValue = m_CurrentID;
		m_CurrentID++;
		m_Tiles[Position.Y][Position.X].StandingUnit = ReturnValue;
		UE_LOG(LogTemp, Warning, TEXT("Registering unit"));
		m_UnitInfos.Add(ReturnValue, UnitInfo());
		m_UnitInfos[ReturnValue].UnitData = MoveTemp(InfoToInsert);
		m_UnitInfos[ReturnValue].Position = Position;
		return(ReturnValue);
	}
	int RuleEngine::GetActivePlayerIndex() const
	{
		return(m_ActivePlayerIndex);
	}
	RuleEngine::RuleEngine(int Width, int Height)
	{
		//return;
		TileInfo EmptyTile;
		m_Tiles.Reserve(Height);
		for (int i = 0; i < Height; i++)
		{
			TArray<TileInfo> NewRow;
			for (int j = 0; j < Width; j++)
			{
				NewRow.Add(EmptyTile);
			}
			m_Tiles.Add(NewRow);
		}
		m_GridWidth = Width;
		m_GridHeight = Height;
	}

	//Mutators
	RuleError RuleEngine::Attack(UnitToken Attacker, UnitToken Defender)
	{
		RuleError ReturnValue = RuleError::Ok;

		if (!(m_UnitInfos.Contains(Attacker) && m_UnitInfos.Contains(Defender)))
		{
			UE_LOG(LogTemp, Warning, TEXT("Didant attack"));
			ReturnValue = RuleError::UnitDoesntExist;
			return(ReturnValue);
		}
		UnitInfo& AttackerInfo = m_UnitInfos[Attacker];
		UnitInfo& DefenderInfo = m_UnitInfos[Defender];
		if (abs(AttackerInfo.Position.X - DefenderInfo.Position.X) + abs(AttackerInfo.Position.Y-AttackerInfo.Position.Y) <= AttackerInfo.UnitData.Range)
		{
			DefenderInfo.UnitData.CurrentHP -= AttackerInfo.UnitData.Damage;
			UE_LOG(LogTemp, Warning, TEXT("Should attack %d %d"), DefenderInfo.UnitData.CurrentHP, AttackerInfo.UnitData.Damage);
			if (DefenderInfo.UnitData.CurrentHP <= 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Destroying"));
				DestroyUnit(Defender);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Didant attack"));
			ReturnValue = RuleError::InvalidPosition;
		}

		return(ReturnValue);
	}
	RuleError RuleEngine::DealDamage(UnitToken AssociatedUnit, int DamageAmount)
	{
		RuleError ReturnValue = RuleError::Ok;


		return(ReturnValue);
	}
	RuleError RuleEngine::DestroyUnit(UnitToken AssociatedUnit)
	{
		RuleError ReturnValue = RuleError::Ok;
		if (!m_UnitInfos.Contains(AssociatedUnit))
		{
			ReturnValue = RuleError::UnitDoesntExist;
			UE_LOG(LogTemp, Warning, TEXT("the fuck"));
			return ReturnValue;
		}
		if (m_CallbackHandler != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Callbacking"));
			m_CallbackHandler->UnitDestroyed(AssociatedUnit);
		}
		UE_LOG(LogTemp, Warning, TEXT("removing rule part"));
		UnitInfo const& Info = m_UnitInfos[AssociatedUnit];
		m_Tiles[Info.Position.Y][Info.Position.X].StandingUnit = 0;
		m_UnitInfos.Remove(AssociatedUnit);
		return(ReturnValue);
	}
	void RuleEngine::SetCallbackHandler(RuleEngineCallbackHandler* CallbackHandler)
	{
		m_CallbackHandler = CallbackHandler;
		UE_LOG(LogTemp, Warning, TEXT("Callbacking %d"),m_CallbackHandler);
	}
	RuleError RuleEngine::MoveUnit(UnitToken AssociatedUnit, UnitPosition NewPosition)
	{
		RuleError ReturnValue = RuleError::Ok;

		if (!m_UnitInfos.Contains(AssociatedUnit))
		{
			ReturnValue = RuleError::UnitDoesntExist;
			return(ReturnValue);
		}
		auto Moves = PossibleMoves(AssociatedUnit);
		if (!Moves.Contains(NewPosition))
		{
			ReturnValue = RuleError::InvalidMove;
			return(ReturnValue);
		}
		UnitInfo& Info = m_UnitInfos[AssociatedUnit];
		m_Tiles[Info.Position.Y][Info.Position.X].StandingUnit = UnitToken(0);
		Info.Position = NewPosition;
		m_Tiles[NewPosition.Y][NewPosition.X].StandingUnit = AssociatedUnit;
		return(ReturnValue);
	}
}