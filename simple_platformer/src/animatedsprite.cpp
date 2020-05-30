#include "animatedsprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture &texture){
	{setTexture(texture);}
}

void AnimatedSprite::sprMove(){
	//todo auto bounds = this->getGlobalBounds();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	{move(      0, -vel_m);}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	{move(      0,  vel_m);}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	{move( -vel_m,      0);}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {move(  vel_m,      0);}
}
