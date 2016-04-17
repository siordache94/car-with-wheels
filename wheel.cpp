#pragma once
#include <SFML/Graphics.hpp>
class Wheel final : public sf::Transformable, public sf::Drawable
{
	public:
		Wheel()
		{
			m_shape.setSize({20.f, 15.f});
			m_shape.setOrigin(m_shape.getSize() / 2.f);
			m_shape.setFillColor(sf::Color(81,81,78));
		}

	private:
		sf::RectangleShape m_shape;
		void draw(sf::RenderTarget& rw, sf::RenderStates states) const override
		{
			states.transform *= getTransform();
			rw.draw(m_shape, states);
		}

};
