#include<SFML/Graphics.hpp>

//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}

// Function to get the position on screen by mouse
void static getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window)
{
	while (true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i p = sf::Mouse::getPosition(window);

			cpos = p.x;
			rpos = p.y;
			break;
		}
	}
}


// Function to print image on screen

