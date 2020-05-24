#include "SFML/Graphics.hpp"

int main(){

	sf::RenderWindow window(sf::VideoMode(800,600,32),"Witaj swiecie");
	sf::Font font;
	sf::RectangleShape shape(sf::Vector2f(20.f,20.f));
	shape.setFillColor(sf::Color::White);

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type==sf::Event::Closed) window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
