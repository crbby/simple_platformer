#pragma once

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Sprite{
public:
	AnimatedSprite(sf::Texture &texture);
	void sprMove();
private:
	float vel_m = 10;

};


