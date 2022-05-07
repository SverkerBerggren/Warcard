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
		if (PossibleMoves <= 0)
		{
			return;
		}
		TArray<MoveDirection> MoveDirections = { {1,0},{0,1},{-1,0},{0,-1} };
		for (auto& Direction : MoveDirections)
		{
			UnitPosition NewPosition = UnitPosition{ CurrentPosition.X + Direction.X, CurrentPosition.Y + Direction.Y };
			if (NewPosition.X <= 0 || NewPosition.X >= m_GridWidth)
			{
				continue;
			}
			if (NewPosition.Y <= 0 || NewPosition.Y >= m_GridHeight)
			{
				continue;
			}
			if (PossibleMoves == 1 && m_Tiles[NewPosition.Y][NewPosition.X].StandingUnit == 0)
			{
				continue;
			}
			if (m_Tiles[NewPosition.Y][NewPosition.X].StandingUnit != 0)
			{
				if (m_UnitInfos[m_Tiles[NewPosition.Y][NewPosition.X].StandingUnit].UnitData.ControllerIndex != Info.UnitData.ControllerIndex)
				{
					continue;
				}
			}
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
			if (i + 1 < Result.Num() && (Result[i].X == Result[i + 1].X && Result[i].Y == Result[i].Y))
			{
				continue;
			}
			ReturnValue.Add(Result[i]);
		}
		return(ReturnValue);
	}
	Unit const& RuleEngine::GetUnitInfo(UnitToken AssociatedUnit) const
	{
		return((Unit const&)(*((Unit*) 123123)));
	}
	UnitToken RuleEngine::RegisterUnit(Unit UnitInfo, UnitPosition Position)
	{
		UnitToken ReturnValue = m_CurrentID;
		m_CurrentID++;
		m_Tiles[Position.Y][Position.X].StandingUnit = ReturnValue;
		m_UnitInfos[ReturnValue].UnitData = MoveTemp(UnitInfo);
		m_UnitInfos[ReturnValue].Position = Position;
		return(ReturnValue);
	}
	int RuleEngine::GetActivePlayerIndex() const
	{
		return(-1);
	}
	RuleEngine::RuleEngine(int Width, int Height)
	{
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
	RuleError RuleEngine::BeginResolve()
	{
		RuleError ReturnValue = RuleError::Ok;


		return(ReturnValue);
	}
	RuleError RuleEngine::MeleeAttack(UnitToken Attacker, UnitToken Defender)
	{
		RuleError ReturnValue = RuleError::Ok;


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


		return(ReturnValue);
	}
	RuleError RuleEngine::MoveUnit(UnitToken AssociatedUnit, UnitPosition NewPosition)
	{
		RuleError ReturnValue = RuleError::Ok;


		return(ReturnValue);
	}
	RuleError RuleEngine::EndResolve()
	{
		RuleError ReturnValue = RuleError::Ok;


		return(ReturnValue);
	}
}