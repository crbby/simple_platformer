#pragma once

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Sprite{
public:
	AnimatedSprite(sf::Texture &texture);
	void sprMove();
private:
	float g = 2.f;
	float vel_m = 10;

};


