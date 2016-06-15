#pragma once
#ifndef _AWESOMIUMMANAGER_H_
#define _AWESOMIUMAMANGER_H_
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <boost/shared_ptr.hpp>
#include <sfml/System.hpp>
#include <graphics/WebTile.h>
#include <boost/unordered_map.hpp>
#include <utilities/awesomium_method_dispatcher.h>
class Engine;

typedef void(*AwesomiumToGameEventBroadcaster)(Engine* engine, const Awesomium::JSArray& args);


class AwesomiumManager
{
public:
	AwesomiumManager(Engine* engine);
	~AwesomiumManager();
	boost::shared_ptr<WebTile> createWebTile(unsigned int width = 800, unsigned int height = 600);
	boost::shared_ptr<WebTile> createWebTileAtURL(unsigned int width = 800, unsigned int height = 600, const std::string& url = std::string());
	Awesomium::WebView* createWebViewAt(unsigned int width = 800, unsigned int height = 600);
	Awesomium::WebView* createWebViewAtURL(unsigned int width = 800, unsigned int height = 600, const std::string& url = std::string());
	//boost::shred_ptr<Awesomium::WebTile> createWebTile
	void update(const sf::Time time);

	void setHTMLRoot(const std::string& rootDir);
	void setHTMLFilePrefix(const std::string& prefix);
	std::string createFileURL(const std::string& file);
	bool addPakFile(const std::string& pakIndex, const std::string& paksource);
	bool removePakFile(const std::string& paksource);
protected:
	void exposeGameObjects(Awesomium::WebView* view);
	void exposeEngineObject(Awesomium::WebView* view);
	void handleJSMethodCall(Awesomium::WebView* view, unsigned int remoteid, const Awesomium::WebString& method_name);

	Awesomium::JSValue JSGetGameTime(Awesomium::WebView* view, const Awesomium::JSArray& args);
	Awesomium::JSValue JSAddSound(Awesomium::WebView* view, const Awesomium::JSArray& args);
	Awesomium::JSValue JSRemoveSound(Awesomium::WebView* view, const Awesomium::JSArray& args);
	Awesomium::JSValue JSNewHTMLScreen(Awesomium::WebView* view, const Awesomium::JSArray& args);
	Awesomium::JSValue JSPopScreen(Awesomium::WebView* view, const Awesomium::JSArray& args);

	Awesomium::JSValue JSBroadcastEvent(Awesomium::WebView* view, const Awesomium::JSArray& args);
	//Awesomium::JSValue JSNewHTMLScreen(Awesomium::WebView* view, const Awesomium::JSArray& args);
	void JSPlaySound(Awesomium::WebView* view, const Awesomium::JSArray& args);
private:
	void loadPakFiles(Awesomium::WebView* view);
	std::string m_HTMLRootDirectory;
	std::string m_HTMLPrefix;
	boost::unordered_map<std::string, std::string> m_pakSources;
	boost::unordered_map<std::string, AwesomiumToGameEventBroadcaster> m_eventBroadcasters;
	Awesomium::WebCore* m_core;
	Engine* m_engine;
	MethodDispatcher m_jsDispatcher;
};

#endif