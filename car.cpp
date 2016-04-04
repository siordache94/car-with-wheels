#pragma once
#include "wheel.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#define M_PI 3.14159265358979323846

class Car final : public sf::Transformable,
	public sf::Drawable
{
	public:

		Car()
		{
			m_body.setSize({100.f, 40.f});
			m_body.setOrigin(0, m_body.getSize().y / 2.f);
			m_wheels[0].setPosition(100.f,  30.f);
			m_wheels[1].setPosition(100.f, -30.f);
			m_wheels[2].setPosition(0,  30.f);
			m_wheels[3].setPosition(0, -30.f);
		}
		enum Direction
		{
			Center,
			Left,
			Right
		};
		sf::Vector2f getSize()
		{
			return m_body.getSize();
		}


		void Turn(int direction)
		{
			switch(direction)
			{
				case Direction::Center:
					{
						if(m_turnAngle < 180)
						{ m_turnAngle += m_lockAngle / 10; }
						else if(m_turnAngle > 180)
						{ m_turnAngle -= m_lockAngle / 10; }
						break;
					}
				case Direction::Right:
					{
						if(m_turnAngle < 180 + m_lockAngle)
						{ m_turnAngle += m_lockAngle / 10; }
						break;
					}
				case Direction::Left:
					{
						if(m_turnAngle > 180 - m_lockAngle)
						{ m_turnAngle -= m_lockAngle / 10; }
						break;
					}
			}
			m_wheels[getExteriorWheel()].setRotation(
			    m_turnAngle);
			m_wheels[getInteriorWheel()].setRotation(
			    calculateIntAngle(calculateCenter(false),
			                      m_wheels[getInteriorWheel()].getPosition()));
			if(m_turnAngle == 180)
			{
				m_wheels[getExteriorWheel()].setRotation(180);
				m_wheels[getInteriorWheel()].setRotation(180);
			}
			//std::cout<<m_turnAngle<<std::endl;
		}
		void Accelerate(int direction)
		{
			m_speed += direction * m_acceleration;
		}
		void Move(float dt)
		{
			if(m_turnAngle == 180)
				this->move(m_speed * cos(getRotation() * 3.14 /
				                         180)*dt, m_speed * sin(getRotation() * 3.14 / 180)
				           *dt);
			else
			{
				float radius = sqrt(pow(((double)
				                         this->getPosition().x -
				                         this->calculateCenter().x),
				                        2.0) + pow((double)this->getPosition().y -
				                                   this->calculateCenter().y, 2.0));
				r = sqrt(pow((center.x - position.x),
				             2.0) + pow((center.y - position.y), 2.0));
				float a = 3 * M_PI / 2 - atan2((center.x -
				                                position.x), (center.y - position.y));
				float x = center.x + cos(a) * r;
				float y = center.y + sin(a) * r;
				return sf::Vector2f(x, y);
			}
		}
		sf::Vector2f calculateCenter(bool absolute =
		                                 false)
		{
			if(absolute)
			{
				if(m_turnAngle == 180)
					return getTransform().transformPoint(sf::Vector2f(
					        0, 0));
				return getTransform().transformPoint(
				           calculateIntersection(
				               m_wheels[getExteriorWheel()].getRotation(),
				               m_wheels[getExteriorWheel() + 2].getRotation(),
				               m_wheels[getExteriorWheel()].getPosition(),
				               m_wheels[getExteriorWheel() + 2].getPosition()));
			}
			else
			{
				return calculateIntersection(
				           m_wheels[getExteriorWheel()].getRotation(),
				           m_wheels[getExteriorWheel() + 2].getRotation(),
				           m_wheels[getExteriorWheel()].getPosition(),
				           m_wheels[getExteriorWheel() + 2].getPosition());
			}
		}
		void stop()
		{
			m_speed = 0;
		}


	private:

		sf::RectangleShape m_body;
		float m_speed = 0;
		float m_turnAngle = 180;
		float m_lockAngle = 50;
		float m_acceleration = 0.1;
		sf::VertexArray m_line;
		sf::VertexArray m_line2;

		std::array<Wheel, 4u> m_wheels;

		void draw(sf::RenderTarget & rw,
		          sf::RenderStates states) const override
		{
			states.transform *= getTransform();
			for(const auto& wheel : m_wheels)
			{ rw.draw(wheel, states); }
			rw.draw(m_body, states);
		}
		int getExteriorWheel()
		{
			if(m_turnAngle < 180)
			{ return 0; }
			else
			{ return 1; }
		}
		int getInteriorWheel()
		{
			if(m_turnAngle >= 180)
			{ return 0; }
			else
			{ return 1; }
		}
		float calculateSlope(float angle)
		{
			if(90 - (int)angle % 180 == 0)
			{ return 1E+10; }
			return tan(angle * M_PI / 180.0);
		}
		float calculateIntAngle(const sf::Vector2f&
		                        center, const sf::Vector2f& wheel)
		{
			return 90 + atan2(wheel.y - center.y,
			                  wheel.x - center.x) * 180 / M_PI;
		}

		sf::Vector2f calculateIntersection(float angle1,
		                                   float angle2, const sf::Vector2f& position1,
		                                   const sf::Vector2f& position2)
		{
			float slope1 = calculateSlope(angle1 - 90);
			float slope2 = calculateSlope(angle2);
			float intercept1 = (slope1 * (-position1.x)) +
			                   position1.y;
			float intercept2 = (slope2 * (-position2.x)) +
			                   position2.y;
			float x = (intercept1 - intercept2) /
			          (slope1 - slope2);
			return sf::Vector2f(x + abs(position1.x -
			                            position2.x), slope1 * x + intercept1 + abs(
			                        position1.y - position2.y));
		}

};
