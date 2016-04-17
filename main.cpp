#include <SFML/Graphics.hpp>
#include <iostream>
#include "car.cpp"

int main()
{
	sf::Clock deltaClock;
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getFullscreenModes().front()), "Click ME", sf::Style::Fullscreen, sf::ContextSettings(24, 8, 8));
	std::cout << "Antialiasing level: " << window.getSettings().antialiasingLevel << std::endl;
	window.setVerticalSyncEnabled(true);
	Car car;
	car.setPosition(400, 300);
	sf::View view;
	view.setSize(window.getSize().x * 2, window.getSize().y * 2);
	window.setView(view);
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{ window.close(); }
		}
		float dt = deltaClock.restart().asMilliseconds();
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		        && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{ car.Turn(Car::Direction::Center); }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{ car.Turn(Car::Direction::Left); }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{ car.Turn(Car::Direction::Right); }
		else
		{ car.Turn(Car::Direction::Center); }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{ car.Accelerate(1); }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{ car.Accelerate(-1); }
		/*  if(car.getPosition().x - car.getSize().x / 2 > window.getSize().x)
		    { car.setPosition(0 - car.getSize().x / 2, car.getPosition().y); }
		    if(car.getPosition().y - car.getSize().y / 2 > window.getSize().y)
		    { car.setPosition(car.getPosition().x, 0 - car.getSize().y / 2); }
		    if(car.getPosition().x + car.getSize().x / 2 < 0)
		    { car.setPosition(window.getSize().x + car.getSize().x / 2, car.getPosition().y); }
		    if(car.getPosition().y + car.getSize().y / 2 < 0)
		    { car.setPosition(car.getPosition().x, window.getSize().y + car.getSize().y / 2); }*/
		car.Move(dt);
		window.clear(sf::Color(43,45,44));
		window.draw(car);
		window.display();
	}
	return 0;
}
