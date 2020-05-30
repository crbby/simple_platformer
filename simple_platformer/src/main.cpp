#include <SFML/Graphics.hpp>
#include <iostream>
#include "animatedsprite.h"

int width  = 1000;
int height = 700;

int main(){

	//render window
	sf::RenderWindow window(sf::VideoMode(width,height),"okno");
	window.setFramerateLimit(60);

	//view
	sf::View view1;

	//player
	sf::Texture guyTexture;
	guyTexture.loadFromFile("guy.png");
	AnimatedSprite guySprite(guyTexture);

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){window.close();}
		}
		//game loop
		window.clear(sf::Color::Black);
		window.setView(view1);
		window.draw(guySprite);
		guySprite.sprMove();
		window.display();
	}

	return EXIT_SUCCESS;
}
