#include"chess.h"
#include<iostream>
#include<conio.h>
#include<SFML/Graphics.hpp>

using namespace std;

//void print(sf::RenderWindow& window)
//{
//	sf::Texture temp;
//	if (!temp.loadFromFile("horse.png"))  //  img ==> file name for image
//	{
//		throw("Unable to load img");
//	}
//
//	sf::Sprite s(temp);
//	s.setScale(0.1, 0.1); //  (width and heigth of image to be printed)
//
//	s.setPosition(10, 10); // position of image
//	window.draw(s);	// draw() will only draw image on backend, image will not display on screen
//	window.display();  // display() will show image on screen
//}
int main() {
	//sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	//print(window);
	chess c;
	c.play();
	/*while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		print(window);
		window.display();
	}*/
	return _getch();
}
