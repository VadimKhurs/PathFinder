#include <Slider.hpp>


namespace visualisation {

	

	Slider::Slider(sf::Vector2f position, sf::Vector2f size, float xthumbSize, float minValue, float maxValue, sf::Vector2f thumbPos ):
		scrollbarPos(position), size(size), minValue(minValue), maxValue(maxValue)
	{	
		scrollbar.setSize(size);
		scrollbar.setFillColor(sf::Color(200, 200, 200));
		scrollbar.setPosition(position);
		scrollbar.setOutlineThickness(4.0f);
		scrollbar.setOutlineColor(sf::Color(0, 0, 0));

		thumb.setFillColor(_getColor(INACTBUT));
		thumb.setPosition(thumbPos); 
		thumb.setSize({xthumbSize, size.y});
	}

	void Slider::draw(sf::RenderWindow& win) const
	{
		win.draw(scrollbar);
		win.draw(thumb);
	}

	float Slider::getValue() const
	{
		return value;
	}

	void Slider::setValue(float value)
	{
		this->value = value;
	}

	sf::Vector2f Slider::getScrollbarPos()
	{
		return scrollbarPos;
	}

	void Slider::setThumbPosition(sf::Vector2f pos)
	{
		thumb.setPosition(pos);
	}

	sf::Vector2f Slider::getThumbPosition() const
	{
		return thumb.getPosition();
	}

	void Slider::logic(sf::Vector2i mouse_pos)
	{
		bool mouseInThumb = thumb.getGlobalBounds().contains(sf::Vector2f(mouse_pos));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && key_up ) {
			if (mouseInThumb) {
				isDragging = true;
				lastMousePosition = mouse_pos;
			}
			else {
				isDragging = false;
			}
		}
		mouseInThumb ? thumb.setFillColor(_getColor(POINTED_BUT)) : thumb.setFillColor(_getColor(INACTBUT));
		

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			isDragging = false;
			key_up = true;

			

		}
		
		if (isDragging) {
			sf::Vector2i mouseDelta = mouse_pos - lastMousePosition;

			float newThumbX = thumb.getPosition().x + mouseDelta.x;
			newThumbX = std::max(scrollbar.getPosition().x, std::min(newThumbX, scrollbar.getPosition().x + scrollbar.getSize().x - thumb.getSize().x));

			thumb.setPosition(newThumbX, thumb.getPosition().y);
			float sliderPercentage = (newThumbX - scrollbar.getPosition().x) / scrollbar.getSize().x;
			value = minValue + (maxValue - minValue) * sliderPercentage;
			lastMousePosition = mouse_pos;

			thumb.setFillColor(_getColor(ACTBUT));
		}

		
	}
}