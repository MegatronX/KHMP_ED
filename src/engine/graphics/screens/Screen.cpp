#include <graphics/screens/Screen.h>

Screen::Screen()
{

}
Screen::~Screen()
{

}

unsigned int Screen::getStackID()
{
	return m_stackID;
}
void Screen::setStackID(const unsigned int stackid)
{
	m_stackID = stackid;
	m_stackIDSet = true;
}
bool Screen::getStackIDSet() const
{
	return m_stackIDSet;
}

bool Screen::handleInput(ev_ptr inputEvent)
{
	return false;
}