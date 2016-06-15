#pragma once
#ifndef _AWESOMIUMSCREEN_H_
#define _AWESOMIUMSCREEN_H_

#include <graphics/Screens/Screen.h>
#include <Awesomium/WebView.h>
#include <Engine.h>

class AwesomiumScreen : public Screen
{
public:
	AwesomiumScreen(Engine* engine, unsigned int width = 1000, unsigned int height = 750, const bool transparent = true);
	AwesomiumScreen(Engine* engine, const std::string& url, unsigned int width = 1000, unsigned int height = 750, const bool transparent = true);
	virtual ~AwesomiumScreen();
	void setURL(const std::string& url);
	void setURL(const std::string& pak, const std::string& url);

	void virtual setStackID(const unsigned int stackid) override;

	virtual bool handleInput(ev_ptr inputEvent) override;

	void update(const sf::Time& time);
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const override;
	void setTransparency(const bool transparent = true) override;
	Awesomium::WebView* getWebView();
protected:
	sf::Texture m_tileTexture;
	sf::Sprite m_tileSprite;
private:
	boost::shared_ptr<Awesomium::WebView> m_webscreen;
	boost::shared_ptr<WebTile> m_tile;
	std::vector<unsigned char> m_rgbaBuffer;
	//bool m_transparent;
};

#endif