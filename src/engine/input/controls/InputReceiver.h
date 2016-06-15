#pragma once
#ifndef _INPUTRECEIVER_H_
#define _INPUTRECEIVER_H_

#include <input/controls/InputModule.h>
#include <events/IEvent.h>

namespace Input
{
	class InputReceiver
	{
	public:
		virtual ~InputReceiver()
		{

		}
		virtual bool handleInput(ev_ptr inputEvent) = 0;
	};
}

#endif