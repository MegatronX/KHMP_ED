#include "WebTile.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <graphics/awesomium.h>
using namespace Awesomium;

WebTile::WebTile(int width, int height) : isTransparent(false), m_width(width), m_height(height)
{
	webView = Awesomium::WebCore::instance()->CreateWebView(width, height);
	rawBuffer.resize(width * height * 4);
}

WebTile::WebTile(Awesomium::WebView* existingWebView, int width, int height) : webView(existingWebView), isTransparent(false) 
{
	rawBuffer.resize(width * height * 4);
}

WebTile::~WebTile() 
{
	webView->Destroy();
}

/*const GLTextureSurface* WebTile::surface() {
	const Awesomium::Surface* surface = webView->surface();
	if (surface)
		return static_cast<const GLTextureSurface*>(surface);

	return 0;
}*/

void WebTile::resize(int width, int height) 
{
	webView->Resize(width, height);
}
void WebTile::setURL(const std::string& url)
{
	//Awesomium::Uri uri = Awesomium::Uri(url, )
	std::string effUrl = m_rootHTML + url;//url;// "Test.html";// "file:///../../resources/Test.html";// m_manager ? m_manager->createFileURL(url) : std::string();// m_rootHTML + url;
	Awesomium::WebURL weburl(WSLit(effUrl.c_str()));
	WebTile::webView->LoadURL(weburl);
}

void WebTile::setURL(const std::string& pakFile, const std::string& url)
{
	std::string effUrl = m_rootHTML + pakFile + "/" + url;//url;// "Test.html";// "file:///../../resources/Test.html";// m_manager ? m_manager->createFileURL(url) : std::string();// m_rootHTML + url;
	Awesomium::WebURL weburl(WSLit(effUrl.c_str()));
	WebTile::webView->LoadURL(weburl);
}

void WebTile::toggleTransparency() 
{
	webView->ExecuteJavascript(WSLit("document.body.style.backgroundColor = 'transparent'"), WSLit(""));
	webView->SetTransparent(isTransparent = !isTransparent);
}