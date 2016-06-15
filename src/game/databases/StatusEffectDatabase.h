#pragma once
#ifndef _SEDB_H_
#define _SEDB_H_

#include <databases/EntityDatabase.h>
#include <components/StatusEffectComponent.h>
namespace KHMP
{
	class StatusEffectDatabase : public EntityDatabase
	{
	public:
		StatusEffectDatabase();
	protected:
		virtual bool validateEntry(entity_ptr se) const override;
	private:
	};
}

#endif