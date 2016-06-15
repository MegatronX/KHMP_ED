#include "awesomium.h"
#include <corrEngine.h>
#include <boost/make_shared.hpp>
#include <Engine.h>
#include <Awesomium/DataPak.h>

#include <events/eventtypes/AudioEvents.h>
#include <events/eventtypes/NewAwesomiumScreenEvent.h>
#include <events/eventtypes/PopWindowEvent.h>
#include <log/Log.h>
#include <graphics/screens/AwesomiumScreen.h>

using namespace Awesomium;

void AwesomiumBroadcast()
{

}

AwesomiumManager::AwesomiumManager(Engine* engine) : m_engine(engine)
{
	WebConfig config;
	//config.
	m_core = WebCore::Initialize(config);

}

AwesomiumManager::~AwesomiumManager()
{
	if (m_core)
		m_core->Shutdown();
}

boost::shared_ptr<WebTile> AwesomiumManager::createWebTile(unsigned int width, unsigned int height)
{
	auto tile = boost::make_shared<WebTile>(width, height);
	loadPakFiles(tile->webView);
	exposeGameObjects(tile->webView);
	tile->m_rootHTML = m_HTMLRootDirectory;
	tile->m_manager = this;
	return tile;
}
boost::shared_ptr<WebTile> AwesomiumManager::createWebTileAtURL(unsigned int width, unsigned int height, const std::string& url)
{
	auto tile = createWebTile(width, height);
	loadPakFiles(tile->webView);
	exposeGameObjects(tile->webView);
	tile->m_rootHTML = m_HTMLRootDirectory;
	tile->m_manager = this;
	tile->setURL(url);
	return tile;
}

Awesomium::WebView*  AwesomiumManager::createWebViewAt(unsigned int width, unsigned int height)
{
	auto view = Awesomium::WebCore::instance()->CreateWebView(width, height);
	loadPakFiles(view);
	exposeGameObjects(view);
	return view;
	//view->session()->
	//boost::make_shared<Awesomium::WebView>(Awesomium::WebCore::instance()->CreateWebView(width, height));
}
Awesomium::WebView* AwesomiumManager::createWebViewAtURL(unsigned int width, unsigned int height, const std::string& url)
{
	auto webView = createWebViewAt(width, height);
	std::string effectiveDir = createFileURL(url);// root + url;
	webView->LoadURL(Awesomium::WebURL(ToWebString(effectiveDir)));
	return webView;
}

void AwesomiumManager::update(const sf::Time time)
{
	m_core->Update();
}

void AwesomiumManager::setHTMLRoot(const std::string& root)
{
	m_HTMLRootDirectory = root;
	
}

void AwesomiumManager::setHTMLFilePrefix(const std::string& prefix)
{
	m_HTMLPrefix = prefix;
}

std::string AwesomiumManager::createFileURL(const std::string& file)
{
	return  m_HTMLPrefix + m_HTMLRootDirectory + file;
}

bool AwesomiumManager::addPakFile(const std::string& pakindex, const std::string& paksource)
{
	auto it = m_pakSources.find(paksource);
	if (it == m_pakSources.end())
	{
		m_pakSources[pakindex] = paksource;
		return true;
	}
	return false;
}

void AwesomiumManager::exposeGameObjects(Awesomium::WebView* view)
{
	if (view)
	{
		
		exposeEngineObject(view);

		view->set_js_method_handler(&m_jsDispatcher);
	}
}

bool AwesomiumManager::removePakFile(const std::string& paksource)
{
	auto it = m_pakSources.find(paksource);
	if (it != m_pakSources.end())
	{
		m_pakSources.erase(it);
		return true;
	}
	return false;
}

void AwesomiumManager::loadPakFiles(Awesomium::WebView* view)
{
	for (auto source = m_pakSources.begin(); source != m_pakSources.end(); ++source)
	{
		auto data_source = new DataPakSource(ToWebString(source->second.c_str()));
		view->session()->AddDataSource(WSLit(source->first.c_str()), data_source);
	}
}

void AwesomiumManager::exposeEngineObject(WebView* view)
{
	if (view)
	{
		JSValue result = view->CreateGlobalJavascriptObject(WSLit("Engine"));
		if (result.IsObject())
		{
			JSObject& engObj = result.ToObject();
			m_jsDispatcher.BindWithRetval(engObj, WSLit("GetGameTime"), JSDelegateWithRetval(this, &AwesomiumManager::JSGetGameTime));
			//m_jsDispatcher.Bind(engObj, WSLit(""), JSDelegate(m_engine, &Engine::Get)


			result = view->CreateGlobalJavascriptObject(WSLit("Engine.AudioSystem"));
			JSObject& audObj = result.ToObject();
			m_jsDispatcher.BindWithRetval(audObj, WSLit("addSound"), JSDelegateWithRetval(this, &AwesomiumManager::JSAddSound));
			m_jsDispatcher.BindWithRetval(audObj, WSLit("removeSound"), JSDelegateWithRetval(this, &AwesomiumManager::JSRemoveSound));
			m_jsDispatcher.Bind(audObj, WSLit("playSound"), JSDelegate(this, &AwesomiumManager::JSPlaySound));

			result = view->CreateGlobalJavascriptObject(WSLit("Engine.ScreenManager"));
			JSObject& smObj = result.ToObject();
			m_jsDispatcher.BindWithRetval(smObj, WSLit("NewHTMLScreen"), JSDelegateWithRetval(this, &AwesomiumManager::JSNewHTMLScreen));
			m_jsDispatcher.BindWithRetval(smObj, WSLit("PopScreen"), JSDelegateWithRetval(this, &AwesomiumManager::JSPopScreen));
		}
		else if (result.IsUndefined())
		{
			auto error = view->last_error();
			int temp = 0;
		}
	}
}

Awesomium::JSValue AwesomiumManager::JSGetGameTime(Awesomium::WebView* view, const Awesomium::JSArray& args)
{
	return JSValue(m_engine->getGameTime().asMilliseconds());
}
Awesomium::JSValue AwesomiumManager::JSAddSound(Awesomium::WebView* view, const Awesomium::JSArray& args)
{
	bool added = false;

	int argCount = args.size();
	if (argCount > 1 && args.At(0).IsString() && args.At(1).IsString())
	{
		boost::shared_ptr<AddAudioRequestEvent> m_request;
		std::string fileName = Awesomium::ToString(args.At(0).ToString());
		std::string indexName = Awesomium::ToString(args.At(1).ToString());
		if (argCount > 2)
		{
			bool isSE = args.At(2).ToBoolean();
			if (argCount > 3)
			{
				std::string world = ToString(args.At(3).ToString());
				if (argCount > 4)
				{
					bool useStored = args.At(4).ToBoolean();
					if (argCount > 5)
					{
						std::string ext = ToString(args.At(5).ToString());
						m_request = boost::make_shared<AddAudioRequestEvent>(fileName, indexName, isSE, world, useStored, ext);
					}
					else
					{
						m_request = boost::make_shared<AddAudioRequestEvent>(fileName, indexName, isSE, world, useStored);
					}
				}
				else
				{
					m_request = boost::make_shared<AddAudioRequestEvent>(fileName, indexName, isSE, world);
				}
			}
			else
			{
				m_request = boost::make_shared<AddAudioRequestEvent>(fileName, indexName, isSE);
			}
		}
		else
		{
			
			///added = m_engine
			m_request = boost::make_shared<AddAudioRequestEvent>(fileName, indexName);
		}
		if (m_request.get())
		{
			m_engine->getEventManager().queueEvent(m_request);
		}
	}
	else
	{
		LOG_DEBUG("Incorrect arguments provided to JSAddSound. Expected > 1 received " << argCount << ". If arg count matched, one of the args was not a a string");
	}
	return JSValue(added);
}
Awesomium::JSValue AwesomiumManager::JSRemoveSound(Awesomium::WebView* view, const Awesomium::JSArray& args)
{
	bool removed = 0;
	int argCount = args.size();
	if (argCount > 0 && args.At(0).IsString())
	{
	}
	return JSValue(removed);
}
void AwesomiumManager::JSPlaySound(Awesomium::WebView* view, const Awesomium::JSArray& args)
{
	int argCount = args.size();
	if (argCount > 0 && args.At(0).IsString())
	{
		boost::shared_ptr<PlayAudioRequestEvent> m_request;
		std::string soundName = Awesomium::ToString(args.At(0).ToString());
		//std::string indexName = Awesomium::ToString(args.At(1).ToString());
		if (argCount > 1)
		{
			if (args.At(1).IsBoolean())
			{
				bool loop = args.At(1).ToBoolean();
				if (argCount > 2)
				{

				}
				else
				{
					m_request = boost::make_shared<PlayAudioRequestEvent>(soundName, loop);
				}
			}
			else if (args.At(1).IsInteger())
			{
				unsigned int channel = static_cast<unsigned int>(args.At(1).ToInteger());
				if (argCount > 2)
				{
					bool loop = args.At(2).ToBoolean();
					m_request = boost::make_shared<PlayAudioRequestEvent>(soundName, channel, loop);
				}
				else
				{

					m_request = boost::make_shared<PlayAudioRequestEvent>(soundName, channel);
				}
			}
		}
		else
		{

			///added = m_engine
			m_request = boost::make_shared<PlayAudioRequestEvent>(soundName, false);
		}
		if (m_request.get())
		{
			m_engine->getEventManager().queueEvent(m_request);
		}
	}
	else
	{
		LOG_DEBUG("Incorrect arguments provided to JSAddSound. Expected > 0 received " << argCount << ". If arg count matched, one of the args was not a a string");
	}
}

Awesomium::JSValue AwesomiumManager::JSNewHTMLScreen(Awesomium::WebView* view, const Awesomium::JSArray& args)
{
	bool added = false;
	int argCount = args.size();
	if (argCount > 0 && args.At(0).IsString())
	{
		/*
		auto awscreenptr = boost::make_shared<AwesomiumScreen>(engine, engine->getGameWindow().getSize().x, engine->getGameWindow().getSize().y);
		awscreenptr->setURL("KHMP/TitleScreen.html");// ("http://www.google.com");
		engine->getScreenManager().pushEntry(awscreenptr, true);
		return true;
		*/
		auto newWindowEvent = boost::make_shared<NewAwesomiumScreenEvent>(ToString(args.At(0).ToString()), m_engine->getGameWindow().getSize().x, m_engine->getGameWindow().getSize().y);
		m_engine->getEventManager().queueEvent(newWindowEvent);
		//auto awscreenptr = boost::make_shared<AwesomiumScreen>(m_engine, m_engine->getGameWindow().getSize().x, m_engine->getGameWindow().getSize().y);
		//exposeEngineObject(awscreenptr->)
		//awscreenptr->setURL(ToString(args.At(0).ToString()));
		//m_engine->getScreenManager().pushEntry(awscreenptr);
	}
	return JSValue(added);
}
Awesomium::JSValue AwesomiumManager::JSPopScreen(Awesomium::WebView* view, const Awesomium::JSArray& args)
{
	bool popTop = true;
	int argCount = args.size();
	if (argCount > 0 && args.At(0).IsInteger())
	{
		popTop = false;
		auto popWindowEvent = boost::make_shared<PopWindowEvent>(false, args.At(0).ToInteger());
		m_engine->getEventManager().queueEvent(popWindowEvent);
	}
	else if (argCount > 0 && args.At(0).IsString())
	{
		auto str = ToString(args.At(1).ToString());
		if (str == "self" || str == "this")
		{
			auto popWindowEvent = boost::make_shared<PopWindowEvent>(view);
			m_engine->getEventManager().queueEvent(popWindowEvent);
		}
	}
	else
	{
		auto popWindowEvent = boost::make_shared<PopWindowEvent>(true);
		m_engine->getEventManager().queueEvent(popWindowEvent);
	}
	return JSValue(false);
}

void AwesomiumManager::handleJSMethodCall(Awesomium::WebView* view, unsigned int remoteid, const Awesomium::WebString& method_name)
{

}