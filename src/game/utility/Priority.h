#pragma once 
#ifndef _PRIORITY_H_
#define _PRIORITY_H_

namespace KHMP
{
	class Priority
	{
	public:
		Priority(const int priority = 0) : m_priority(priority)
		{

		}

		void setPriority(const int priority = 0)
		{
			m_priority = priority;
		}
		int getPriority() const
		{
			return m_priority;
		}
	protected:
		int m_priority;
	private:

	};
}

#endif