#pragma once
#ifndef _WEBTILE_H_
#define _WEBTILE_H_
#include <Awesomium/WebView.h>
#include <string>
#include <vector>
class AwesomiumManager;

class WebTile
{
public:
	Awesomium::WebView* webView;
	std::vector<unsigned char> rawBuffer;
	unsigned int m_width;
	unsigned int m_height;
	bool isTransparent;

	WebTile(int width, int height);
	WebTile(Awesomium::WebView* existingWebView, int width, int height);
	~WebTile();

	//const GLTextureSurface* surface();
	void setURL(const std::string& url);
	void setURL(const std::string& pakFile, const std::string& url);
	void resize(int width, int height);
	void toggleTransparency();
	std::string m_rootHTML;
	AwesomiumManager* m_manager;
};

#endif