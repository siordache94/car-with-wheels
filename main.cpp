#include <SFML/Graphics.hpp>
#include <iostream>
#include "car.cpp"

int main()
{
	sf::Clock deltaClock;
	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(1);
	circle.setPointCount(100);
	sf::RenderWindow window(sf::VideoMode(
	                            sf::VideoMode::getFullscreenModes().front()), "Click ME", sf::Style::Fullscreen,
	                        sf::ContextSettings(24, 8, 8));
	std::cout << "Antialiasing level: " << window.getSettings().antialiasingLevel <<
	          std::endl;
	sf::RectangleShape cube(sf::Vector2f(10, 10));
	sf::RectangleShape cube1(sf::Vector2f(10, 10));
	cube1.setFillColor(sf::Color::Red);
	cube.setOrigin(cube.getSize() / 2.f);
	cube1.setOrigin(cube1.getSize() / 2.f);
	window.setVerticalSyncEnabled(true);
	//create car
	Car car;
	car.setPosition(400, 300);
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		float dt = deltaClock.restart().asMilliseconds();
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		        && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			car.Turn(Car::Direction::Center);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			car.Turn(Car::Direction::Left);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			car.Turn(Car::Direction::Right);
		else
			car.Turn(Car::Direction::Center);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			car.Accelerate(1);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			car.Accelerate(-1);
		if(car.getPosition().x - car.getSize().x / 2 > window.getSize().x)
			car.setPosition(0 - car.getSize().x / 2, car.getPosition().y);
		if(car.getPosition().y - car.getSize().y / 2 > window.getSize().y)
			car.setPosition(car.getPosition().x, 0 - car.getSize().y / 2);
		if(car.getPosition().x + car.getSize().x / 2 < 0)
			car.setPosition(window.getSize().x + car.getSize().x / 2, car.getPosition().y);
		if(car.getPosition().y + car.getSize().y / 2 < 0)
			car.setPosition(car.getPosition().x, window.getSize().y + car.getSize().y / 2);
		car.rotate(-1);
		car.Move(dt);
		cube.setPosition(car.calculateCenter(true));
		cube1.setPosition(car.getPosition());
		circle.setPosition(cube.getPosition());
		circle.setRadius(sqrt(pow(((double)car.getPosition().x - cube.getPosition().x),
		                          2.0) + pow((double)car.getPosition().y - cube.getPosition().y, 2.0)));
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		window.clear();
		window.draw(car);
		window.draw(cube);
		window.draw(circle);
		window.draw(cube1);
		window.display();
	}
	return 0;
}
