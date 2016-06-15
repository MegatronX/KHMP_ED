#pragma once
#ifndef _IANIMATOR_H_
#define _IANIMATOR_H_

#include <boost/function.hpp>

namespace KHMP
{
	template <class Animated, typename id>
	class Animator
	{
	public:
		typedef boost::function<void(Animated&, float)> AnimationSignature;
	protected:
	private:
	};
}

#endif