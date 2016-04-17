#include "line.h"


Line::Line() {};
Line::Line(float angle, sf::Vector2f point):
	m_slope(calculateSlope(angle)),
	m_intercept((m_slope * (-point.x)) + point.y)
{
}
Line::Line(sf::Vector2f first, sf::Vector2f second):
	m_slope(calculateSlope(first, second)),
	m_intercept((m_slope * (-first.x)) + first.y)
{
}
sf::Vector2f Line::getPoint(float x)
{
	return sf::Vector2f(x, m_slope * x + m_intercept);
}
void Line::setSlope(float angle)
{
	m_slope = calculateSlope(angle);
}
void Line::setPoint(sf::Vector2f point)
{
	m_intercept = (m_slope * (-point.x)) + point.y;
}
float Line::getSlope()
{
	return m_slope;
}
float Line::calculateSlope(float angle)
{
	if(90 - (int)angle % 180 == 0)
	{ return 1E+10; }
	return tan(angle * M_PI / 180.0);
}
float Line::calculateSlope(sf::Vector2f first, sf::Vector2f second)
{
	return atan2(first.x - second.x, first.y - second.y) * 180 / M_PI;
}
float Line::getIntercept()
{
	return m_intercept;
}

sf::Vector2f getIntersection(Line other)
{
	float x = (other.getIntercept() - Line::m_intercept) / (other.getSlope() - Line::m_slope);
	return -sf::Vector2f(x, Line::m_slope * x + Line::m_intercept);
}
static sf::Vector2f getIntersection(Line first, Line second)
{
	float x = (second.getIntercept() - first.getIntercept()) / (second.getSlope() - first.getSlope());
	return -sf::Vector2f(x, first.getSlope() * x + first.getIntercept());
}
void Line::draw(sf::RenderTarget& rw, sf::RenderStates states) const override
{
	states.transform *= getTransform();
	for(const auto& wheel : m_wheels)
	{
		rw.draw(wheel, states);
	}
	rw.draw(m_body, states);
}

