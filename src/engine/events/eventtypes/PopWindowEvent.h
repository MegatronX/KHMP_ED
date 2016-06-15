#pragma once
#ifndef _POPWINDOWEVENT_H_
#define _POPWINDOWEVENT_H_

#include <events/IEvent.h>
#include <Awesomium/WebView.h>
class PopWindowEvent : public IEvent
{
public:
	static const EventType m_eventSignature = 0x34B1101f;
	PopWindowEvent(const bool topWindow, const unsigned int windowID = 0) : IEvent(m_eventSignature), m_popTop(topWindow), m_popScreenID(windowID)
	{

	}
	PopWindowEvent(Awesomium::WebView* windowToPop) : IEvent(m_eventSignature), m_popTop(false)
	{
		m_useAweomiumWindowPtr = true;
		m_awesomiumWindow = windowToPop;
	}
	bool popTopWindow() const
	{
		return m_popTop;
	}
	bool useAwesomiumWindowPtr() const
	{
		return m_useAweomiumWindowPtr;
	}
	unsigned int popWindowID() const
	{
		return m_popScreenID;
	}
	Awesomium::WebView* getWebView()
	{
		return m_awesomiumWindow;
	}
protected:
	bool m_popTop;
	bool m_useAweomiumWindowPtr;
	unsigned int m_popScreenID;
	Awesomium::WebView* m_awesomiumWindow;
};

#endif