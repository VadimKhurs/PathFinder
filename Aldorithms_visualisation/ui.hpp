#pragma once
#include <path.hpp>

extern sf::Font font;

extern float delta_mouse;



class Button {
public:
	sf::RectangleShape* rect;
	sf::Text text;

	bool clickObj = false;

	Button(std::string text, bool state,
		sf::Vector2f pos, sf::Vector2f size, int CharSize);

	bool checkValidClick(sf::Vector2i mousePos) const;
	void setState(bool state);
	bool getState() const;

	void draw(sf::RenderWindow& win) const;

	bool setColor(int i, const bool LMousePressed, sf::Vector2i mouse_pos); //set color to create other button's types 
private:
	
	bool state;
	sf::Vector2f pos;
	sf::Vector2f size;
	
};

namespace visualisation {

		namespace ui {
			
			void events(bool LMousePressed, sf::RenderWindow& win);

			extern Button* buttons[16];
			extern Button* exitButton;
			extern sf::Text text;

			extern Slider* sizeSlider;
			extern Slider* animSpeedSlider;
			extern Slider* SoundVolumeSlider;

			//Initialize all texts, font, etc.
			void initUi();
			//render buttons, sliders, text
			void renderUi(sf::RenderWindow& win);

			void renderText(sf::RenderWindow& win,
				const std::string& string, sf::Vector2f position, float scale,
				sf::Color fillColor
			);

		}
	
}


