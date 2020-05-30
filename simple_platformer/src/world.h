#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

class World{
public:
	World(std::vector<sf::Texture>&textures_);
	std::vector<sf::Sprite>worldDraw();
	void getTextureSize();
	void keyboardHandler(sf::View &view);
private:
	std::vector<sf::Texture>textures;

};

#endif // WORLD_H
