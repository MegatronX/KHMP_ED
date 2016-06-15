#pragma once
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include <actions/Action.h>

namespace KHMP
{
	class Attack : public Action
	{
	public:
		//Attack(Entity* owner, const ComponentID id);
		Attack(boost::shared_ptr<Entity> owner, const ComponentID id, float basePower = 0.f, float accuracy = 0.95f, float critChance = 0.125f, float magicWgt = 0.f, float physWeight = 1.f);
		Attack(Entity* owner, const ComponentID id, float basePower = 0.f, float accuracy = 0.95f, float critChance = 0.125f, float magicWgt = 0.f, float physWeight = 1.f);

		bool getIsCritical() const;
		void setIsCritical(const bool crit);

		float getFinalPower() const;
		void setFinalPower(const float power);

		float getBasePower() const;
		void setBasePower(const float power);

		void setCriticalHitChance(const float chance);
		float getCriticalChance() const;

		float getMagicWeight() const;
		void setMagicWeight(const float weight);

		float getPhysicalWeight() const;
		void setPhysicalWeight(const float weight);

		int getCalculatedDamage() const;
		void setCalculatedDamage(const int dmg = 0);

		virtual RawClonePtr rawClone() const override;
	protected:
		
		bool m_isCritical;
		float m_finalPower;

		//below stats are generally fixed
		float m_critChance;
		float m_magicWeight;
		float m_physicalWeight;

		//base power should almost always be fixed
		float m_basePower;

		int m_calcualtedDamage;
	private:
	};
}

#endif