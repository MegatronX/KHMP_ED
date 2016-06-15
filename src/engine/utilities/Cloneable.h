#pragma once
#ifndef _CLONEABLE_H_
#define _CLONEABLE_H_
#include <boost/shared_ptr.hpp>

template <class T>
class ICloneable
{
public:
	typedef boost::shared_ptr<T> ClonePtr;
	typedef T* RawClonePtr;

	template <class P>
	boost::shared_ptr<P> cloneAs() const
	{
		return boost::dynamic_pointer_cast<P>(clone());
	}

	virtual ClonePtr clone() const
	{
		return ClonePtr(rawClone());
	}

	virtual RawClonePtr rawClone() const
	{
		return nullptr;// RawClonePtr(new T(*this));
	}
};


#endif