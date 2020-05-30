#include "world.h"
#include <iostream>

World::World(std::vector<sf::Texture>&textures_){
	std::copy(textures_.begin(),textures_.end(),std::back_inserter(textures));
}

void World::getTextureSize(){
	{std::cout<<textures.size();};
}

std::vector<sf::Sprite> World::worldDraw(){
	std::vector<sf::Sprite>map;

	//temp
	sf::Sprite wallSprite;
	wallSprite.setTexture(textures[0]);
	wallSprite.setPosition(0,600);
	map.emplace_back(wallSprite);

	return map;
}

void World::keyboardHandler(sf::View &view){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {view.move( 10,  0);}	//left
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {view.move(-10,  0);}	//right
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {view.move(  0, -10);}	//down
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {view.move(  0,  10);}	//up
}
