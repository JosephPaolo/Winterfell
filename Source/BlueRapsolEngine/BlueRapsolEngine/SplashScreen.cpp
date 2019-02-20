#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow) {
	sf::Texture texture;

	if (!texture.loadFromFile("../../../Assets/SplashTex.png")) {
		OutputDebugString(L"\n[Error] Cannot load splash texture.");
		return;
	}

	sf::Sprite sprite(texture);
	sf::Event event;

	while (renderWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { // "close requested" event: we close the window
			renderWindow.close();
		}
	}

	renderWindow.clear(sf::Color::Black); //Clear the window with black color
	renderWindow.draw(sprite); //Draw everything here...
	renderWindow.display(); //End the current frame

}