
#include <Engine.h>
#include <EngineTests.h>


#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

void main()
{
	try
	{
		Engine gameEngine("Config.xml");
		//testEngine(&gameEngine);
		//musicTest(&gameEngine, "Dearly Beloved");

		//statManagerTest(&gameEngine);// , ent);

		//timingWindowTest(&gameEngine);
		//mechanicsTest(&gameEngine);
		//attacksTest(&gameEngine);
		//int x;
		//std::cin >> x;
		bool running = true;
		bool added = true;
		htmlWindowTest(&gameEngine);
		bigTextureTest();
		//auto webview = gameEngine.getAwesomiumManager().createWebViewAtURL(600, 600, std::string("http:/www.google.com"));
		//Awesomium::WebView* webview = Awesomium::WebCore::instance()->CreateWebView(800, 600);
		//Awesomium::WebString str = Awesomium::WSLit("http:/www.google.com");
		//webview->LoadURL(Awesomium::WebURL(str));
		bool res2dump = true;
		while (running)
		{
			gameEngine.pollWindowEvents();
			running = gameEngine.update();
			//screen.update(gameEngine.getRealTime());
			//gameEngine.draw();
			//screen.draw(gameEngine.getGameWindow());
			auto time = gameEngine.getRealTime();
			gameEngine.draw();
			
			if (added && time > sf::milliseconds(90000))
			{
				freeEngine(&gameEngine);
				added = false;
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cerr << "Exception occured " << ex.what() << std::endl;
	}
}