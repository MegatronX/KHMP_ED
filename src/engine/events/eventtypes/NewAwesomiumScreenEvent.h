#pragma once
#ifndef _NEWAWESOMIUMSCREEN_H_
#define _NEWAWESOMIUMSCREEN_H_

#include <events/IEvent.h>

class NewAwesomiumScreenEvent : public IEvent
{
public:
	static const EventType m_eventSignature = 0x8c811A1f;
	NewAwesomiumScreenEvent(const std::string& url, const unsigned int width, const unsigned int height);

	const std::string& getURL() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
protected:
	std::string m_url;
	unsigned int m_width;
	unsigned int m_height;
};

#endif