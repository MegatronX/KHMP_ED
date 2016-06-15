#include <actions/Attack.h>

namespace KHMP
{

	Attack::Attack(boost::shared_ptr<Entity> owner, const ComponentID id, float basePower, float accuracy, float critChance, float magicWgt, float physWeight) :
		Action(owner, id, accuracy), m_basePower(basePower), m_critChance(critChance), m_magicWeight(magicWgt), m_physicalWeight(physWeight), m_finalPower(basePower), m_isCritical(false)
	{

	}
	Attack::Attack(Entity* owner, const ComponentID id, float basePower, float accuracy, float critChance, float magicWgt, float physWeight) : 
		Action(owner, id, accuracy), m_basePower(basePower),m_critChance(critChance), m_magicWeight(magicWgt), m_physicalWeight(physWeight), m_finalPower(basePower), m_isCritical(false)
	{

	}

	bool Attack::getIsCritical() const
	{
		return m_isCritical;
	}
	void Attack::setIsCritical(const bool crit)
	{
		m_isCritical = crit;
	}

	float Attack::getFinalPower() const
	{
		return m_finalPower;
	}
	void Attack::setFinalPower(const float power)
	{
		m_finalPower = power;
	}

	float Attack::getBasePower() const
	{
		return m_basePower;
	}
	void Attack::setBasePower(const float power)
	{
		m_basePower = power;
	}

	void Attack::setCriticalHitChance(const float chance)
	{
		m_critChance = chance;
	}

	float Attack::getCriticalChance() const
	{
		return m_critChance;
	}

	float Attack::getMagicWeight() const
	{
		return m_magicWeight;
	}
	void Attack::setMagicWeight(const float weight)
	{
		m_magicWeight = weight;
	}

	float Attack::getPhysicalWeight() const
	{
		return m_physicalWeight;
	}
	void Attack::setPhysicalWeight(const float weight)
	{
		m_physicalWeight = weight;
	}

	int Attack::getCalculatedDamage() const
	{
		return m_calcualtedDamage;
	}
	void Attack::setCalculatedDamage(const int dmg)
	{
		m_calcualtedDamage = dmg;
	}

	Attack::RawClonePtr Attack::rawClone() const
	{
		return RawClonePtr(new Attack(*this));
	}

}