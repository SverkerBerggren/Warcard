#include "RuleEngine.h"


namespace WCE
{
	//Observers
	UnitPosition RuleEngine::GetUnitPosition(UnitToken AssociatedUnit) const
	{
		UnitPosition ReturnValue;

		return(ReturnValue);
	}
	TArray<UnitPosition> RuleEngine::PossibleMoves(UnitToken AssociatedUnit) const
	{
		TArray<UnitPosition> ReturnValue;

		return(ReturnValue);
	}
	Unit const& RuleEngine::GetUnitInfo(UnitToken AssociatedUnit) const
	{
		return((Unit const&)(*((Unit*) 123123)));
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