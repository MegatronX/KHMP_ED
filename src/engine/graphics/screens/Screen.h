#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <Entity/Entity.h>
#include <graphics/IAnimatedDraw.h>
#include <input/controls/InputReceiver.h>

class Screen : public IAnimatedDraw, public Input::InputReceiver
{
public:
	Screen();
	~Screen();

	unsigned int virtual getStackID();
	void virtual setStackID(const unsigned int stackid);
	bool virtual getStackIDSet() const;

	virtual bool handleInput(ev_ptr inputEvent) override;
protected:
private:
	unsigned int m_stackID;
	bool m_stackIDSet;
};

typedef boost::shared_ptr<Screen> screen_ptr;

#endif