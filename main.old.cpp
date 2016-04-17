if(abs(m_wheels[0].getRotation() - 180) < 60)
{
	m_wheels[0].rotate(direction);
	m_wheels[1].rotate(direction);
}

void Centralize()
{
	if(abs(m_wheels[0].getRotation() - 180) < 1)
	{
		m_wheels[0].setRotation(180);
		m_wheels[1].setRotation(180);
	}
	else if(m_wheels[0].getRotation() < 179)
	{
		m_wheels[0].rotate(1);
		m_wheels[1].rotate(1);
	}
	else if(m_wheels[0].getRotation() > 181)
	{
		m_wheels[0].rotate(-1);
		m_wheels[1].rotate(-1);
	}
}



float calculateSlope(float angle)
{
	angle -= 90;
	if(90 - (int)angle % 180 == 0)
	{ return 1E+10; }
	return tan(angle * M_PI / 180.0);
}


sf::Vector2f getIntersection(float& angle1, float& angle2, sf::Vector2f& position1, sf::Vector2f& position2)
{
	float slope1 = calculateSlope(angle1);
	float slope2 = calculateSlope(angle2);
	float intercept1 = (slope1 * (-position1.x)) + position1.y;
	float intercept2 = (slope2 * (-position2.x)) + position2.y;
	float x = (intercept2 - intercept1) / (slope2 - slope1);
	return -sf::Vector2f(x, slope1 * x + intercept1);
}














classe.method
s
