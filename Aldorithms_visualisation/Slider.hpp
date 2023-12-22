#pragma once
#include <grid.hpp>

namespace visualisation {

	

	class Slider {
	public:
		sf::Vector2f size;


		Slider(sf::Vector2f position, sf::Vector2f size, float xthumbSize, float minValue, float maxValue, sf::Vector2f thumbPos);

		void draw(sf::RenderWindow& win) const;

		float getValue() const;

		void setValue(float value);

		sf::Vector2f getScrollbarPos();

		void setThumbPosition(sf::Vector2f pos);

		sf::Vector2f getThumbPosition() const;

		void logic(sf::Vector2i mouse_pos);




	private:
		sf::RectangleShape scrollbar;
		sf::RectangleShape thumb;
		
		bool isDragging = false;
		float minValue;
		float maxValue;
		float value = maxValue / 2;
		
		sf::Vector2f scrollbarPos;

		sf::Vector2i lastMousePosition;
	};


	

}