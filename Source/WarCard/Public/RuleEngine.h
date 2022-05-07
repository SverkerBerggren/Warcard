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

	struct Unit
	{
		TArray<TUniquePtr<Effect>> Effects;
		int MovementSpeed = 0;
		int MeeleDamage = 0;
		int CurrentHP = 0;
	};


	class RuleEngine
	{
	private:
		struct UnitInfo
		{
			Unit UnitData;
			UnitPosition Position;
		};

		TMap<UnitToken, UnitInfo> m_UnitInfos;
	public:

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