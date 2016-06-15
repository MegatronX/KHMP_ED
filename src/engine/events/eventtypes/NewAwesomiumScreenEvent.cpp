#include <events/eventtypes/NewAwesomiumScreenEvent.h>

NewAwesomiumScreenEvent::NewAwesomiumScreenEvent(const std::string& url, const unsigned int width, const unsigned int height) : IEvent(m_eventSignature), m_url(url), m_width(width), m_height(height)
{

}

const std::string& NewAwesomiumScreenEvent::getURL() const
{
	return m_url;
}
unsigned int NewAwesomiumScreenEvent::getWidth() const
{
	return m_width;
}
unsigned int NewAwesomiumScreenEvent::getHeight() const
{
	return m_height;
}