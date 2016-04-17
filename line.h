#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#define M_PI 3.14159265358979323846
class Line
{
	public:
		Line();
		Line(float angle, sf::Vector2f point);
		Line(sf::Vector2f first, sf::Vector2f second);
		sf::Vector2f getPoint(float x);
		void setSlope(float angle);
		void setPoint(sf::Vector2f point);
		float getSlope();
		float calculateSlope(float angle);
		float calculateSlope(sf::Vector2f first, sf::Vector2f second);
		float getIntercept();
	private:
		float m_slope;
		float m_intercept;
		void draw(sf::RenderTarget& rw, sf::RenderStates states) const;

};
