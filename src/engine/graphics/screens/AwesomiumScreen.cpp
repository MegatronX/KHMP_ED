#include <graphics/screens/AwesomiumScreen.h>
#include <Awesomium/BitmapSurface.h>

#include <events/eventtypes/InputActionEvent.h>

using namespace Awesomium;
//using namespace KHMP;
AwesomiumScreen::AwesomiumScreen(Engine* engine, unsigned int width, unsigned int height, const bool transparent)// : m_tile(800, 600)
{
	m_tile = engine->getAwesomiumManager().createWebTile(width, height);
	m_tileTexture.create(m_tile->m_width, m_tile->m_height);
	//m_tile->webView->
	setTransparency(transparent);
	m_rgbaBuffer.resize(width * height * 4);// *8);
}
AwesomiumScreen::AwesomiumScreen(Engine* engine, const std::string& url, unsigned int width, unsigned int height, const bool transparent)
{
	m_tile = engine->getAwesomiumManager().createWebTile(width, height);
	m_tileTexture.create(m_tile->m_width, m_tile->m_height);
	//m_tile->webView->
	setTransparency(transparent);
	m_rgbaBuffer.resize(width * height * 4);// *8);
	setURL(url);
}
AwesomiumScreen::~AwesomiumScreen()
{
	
}
void AwesomiumScreen::setURL(const std::string& url)
{
	m_tile->setURL(url);
}

void AwesomiumScreen::setURL(const std::string& pak, const std::string& url)
{
	m_tile->setURL(pak, url);
}

void AwesomiumScreen::setStackID(const unsigned int stackid)
{
	Screen::setStackID(stackid);
}

bool AwesomiumScreen::handleInput(ev_ptr inputEvent)
{
	bool handled = false;
	if (inputEvent->getEventType() == InputActionEvent::m_eventSignature)
	{
		auto actionEvent = boost::dynamic_pointer_cast<InputActionEvent>(inputEvent);
		if (actionEvent)// && actionEvent->isHandled())
		{
			JSValue input = m_tile->webView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));
			if (input.IsObject())
			{
				JSArray inputArgs;
				inputArgs.Push(JSValue(actionEvent->getAction()));
				inputArgs.Push(JSValue(actionEvent->isActionPushed()));
				inputArgs.Push(JSValue(actionEvent->getPlayer()));
				inputArgs.Push(JSValue(actionEvent->getTimeStamp().asMilliseconds()));
				JSValue inputhandled = input.ToObject().Invoke(WSLit("handleInput"), inputArgs);
				if (inputhandled.IsBoolean())
				{
					handled = inputhandled.ToBoolean();
				}
			}
			//actionEvent->
		}
		//Awesomium::WebKeyboardEvent keyboardEvent;
		//keyboardEvent.
		//	m_tile->webView->InjectKeyboardEvent()
	}
	return handled;
}

void AwesomiumScreen::update(const sf::Time& time)
{
	//static bool printfirst = false;
	if (!m_tile->webView->IsLoading())
	{
		Awesomium::BitmapSurface* surface = (Awesomium::BitmapSurface*)m_tile->webView->surface();
		if (surface && surface->is_dirty())
		{
			/*if (!printfirst && time > sf::milliseconds(20000))
			{
				//m_tile->webView->ExecuteJavascript(WSLit("document.body.style.backgroundColor = 'transparent'"), WSLit(""));
				//m_tile->webView->SetTransparent(true);
				surface->SaveToPNG(WSLit("testres.png"));//->SaveToJPEG(WSLit("res.jpg"));
				printfirst = true;
			}*/
			surface->CopyTo(m_rgbaBuffer.data(), surface->width() * 4, 4, true, false);
			m_tileTexture.update(m_rgbaBuffer.data());// const_cast<const sf::Uint8*>(surface->buffer()), surface->width(), surface->height(), 0, 0);
			m_tileSprite.setTexture(m_tileTexture, true);
		}
		m_draw = true;
	}
	else
	{
		m_draw = false;
	}
}
void AwesomiumScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_draw && m_tile->webView->surface())
	{
		target.draw(m_tileSprite);
	}
}

void AwesomiumScreen::setTransparency(const bool transparent)
{
	Screen::setTransparency(transparent);
	m_tile->webView->SetTransparent(true);
}

Awesomium::WebView* AwesomiumScreen::getWebView()
{
	return m_tile->webView;
}