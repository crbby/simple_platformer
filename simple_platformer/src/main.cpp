#include <SFML/Graphics.hpp>
#include <iostream>
#include "animatedsprite.h"
#include "world.h"

int width  = 1000;
int height = 700;


int main(){

	//text
	std::vector<sf::Texture>toLoad;

	sf::Texture wallTexture;
	wallTexture.loadFromFile("wall.png");
	toLoad.emplace_back(wallTexture);

	//window init
	sf::RenderWindow window(sf::VideoMode(width,height),"og kno");
	window.setFramerateLimit(60);

	//player texture and sprite
	sf::Texture guyTexture;
	guyTexture.loadFromFile("guy.png");
	AnimatedSprite guySprite(guyTexture);

	//camera
	sf::View view1;
	view1.setCenter(0,0);

	//world
	World world1(toLoad);
	world1.getTextureSize();

	while(window.isOpen()){

		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){window.close();}

		}

		window.clear(sf::Color(130, 180, 250));
		//game loop here
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {window.close();}

		guySprite.sprMove();

		//for(const auto &s : world1.worldDrawPtr()){window.draw(*s);}

		window.setView(view1);
		world1.keyboardHandler(view1);
		window.draw(guySprite);

		for(const auto &s : world1.worldDraw()){window.draw(s);}

		window.display();

	}




	return EXIT_SUCCESS;
}

