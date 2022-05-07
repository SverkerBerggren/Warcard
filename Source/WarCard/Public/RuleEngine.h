#pragma once
#include <cstdint>
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "Templates/UniquePtr.h"
#include "Containers/UnrealString.h" 
namespace WCE
{
	typedef int32_t UnitToken;

	struct UnitPosition
	{
		int X;
		int Y;
		bool operator<(UnitPosition const& rhs) const
		{
			if (X < rhs.X)
			{
				return(true);
			}
			else if (X == rhs.X)
			{
				if (Y < rhs.Y)
				{
					return(true);
				}
			}
			return(false);
		}
	};

	enum class RuleError
	{
		Ok,
		UnitDoesntExist,
	};


	FString RuleErrorToString(RuleError ErrorToConvert);

	enum class EffectType
	{
		Trigger,
		Continous,
		Activated,

		Manual
	};
	class RuleEngine;

	class Effect
	{
	public:


		virtual FString GetString() = 0;
		virtual ~Effect()
		{

		}
	};

	class Effect_Manual
	{
	public:
		void* PrivateData = nullptr;
		void(*Effect)(RuleEngine& Engine, void* PrivateData) = nullptr;
		void (*FreeData)(void*) = nullptr;
		~Effect_Manual()
		{
			if (FreeData != nullptr)
			{
				FreeData(PrivateData);
			}
		}
	};
	typedef uint32_t UnitType;
	struct Unit
	{
		int ControllerIndex = 0;
		UnitType Type = 0;
		TArray<TUniquePtr<Effect>> Effects;
		int ActivationCost = 0;
		int MovementSpeed = 0;
		int Range = 0;
		int Damage = 0;
		int CurrentHP = 0;
	};

	struct TileInfo
	{
		UnitToken StandingUnit = 0;
	};

	struct UnitInfo
	{
		Unit UnitData;
		UnitPosition Position;
	};

	class RuleEngine
	{
	private:
		UnitToken m_CurrentID = 1;
		TMap<UnitToken, UnitInfo> m_UnitInfos;

		int m_GridWidth = 0;
		int m_GridHeight = 0;
		TArray<TArray<TileInfo>> m_Tiles;

		void i_RecursiveTraversal(UnitInfo const& Info, UnitPosition CurrentPosition, int PossibleMoves, TArray<UnitPosition>& OutResult) const;
	public:
		RuleEngine() {};
		RuleEngine(int Width, int Height);

		//Observers
		UnitPosition GetUnitPosition(UnitToken AssociatedUnit) const;
		TArray<UnitPosition> PossibleMoves(UnitToken AssociatedUnit) const;
		Unit const& GetUnitInfo(UnitToken AssociatedUnit) const;
		int GetActivePlayerIndex() const;


		//Mutators
		UnitToken RegisterUnit(Unit UnitInfo, UnitPosition Position);
		RuleError BeginResolve();
		RuleError MeleeAttack(UnitToken Attacker, UnitToken Defender);
		RuleError DealDamage(UnitToken AssociatedUnit, int DamageAmount);
		RuleError DestroyUnit(UnitToken AssociatedUnit);
		RuleError MoveUnit(UnitToken AssociatedUnit, UnitPosition NewPosition);
		RuleError EndResolve();
	};
}