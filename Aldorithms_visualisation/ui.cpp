#include <ui.hpp>
sf::Font font;
float delta_mouse = 0;




Button::Button(
	std::string text_,
	bool state_,
	sf::Vector2f pos_,
	sf::Vector2f size_,
	int CharSize) :state(state_), pos(pos_), size(size_)
{
	text.setFont(font);
	text.setString(text_);
	text.setCharacterSize(CharSize);

	text.setFillColor(sf::Color::White);

	text.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text.getLocalBounds();

	text.setPosition(pos.x + size.x / 2 - textBounds.width / 2,
		pos.y + size.y / 2 - textBounds.height / 2 - 4);

	rect = new sf::RectangleShape{ size };
	rect->setPosition(pos);
}

bool Button::checkValidClick(sf::Vector2i mousePos) const
{
	return rect->getGlobalBounds().contains(sf::Vector2f(mousePos));
	//return (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x
	//	&& mousePos.y >= pos.y && mousePos.y <= pos.y + size.y);
}

void Button::setState(bool _state)
{
	this->state = _state;
}

bool Button::getState() const
{
	return state;
}

void Button::draw(sf::RenderWindow& win) const
{
	win.draw(*rect);
	win.draw(text);
}

bool Button::setColor(int i, const bool LMousePressed, sf::Vector2i mouse_pos)
{

	if (i > 8) {
		i > 11 ? rect->setFillColor(sf::Color::White) : rect->setFillColor(_getColor(INACTBUT));
	}
	else {
		rect->setFillColor(_getColor(INACTBUT));
	}

	

	if (i > 8) {
		if (this->state) {
			i > 11 ? rect->setFillColor(_getColor(ACTBUT)) : rect->setFillColor(_getColor(INACTBUT));
			
		}
		else {
			i > 11 ? rect->setFillColor(_getColor(INACTBUT)) : rect->setFillColor(sf::Color::White);
		}
	}

	if (checkValidClick(mouse_pos)) {
		if (i < 9)
			rect->setFillColor(_getColor(POINTED_BUT));
		
		if (LMousePressed && key_up) {
			if (i < 9 && !clickObj) {
				clickObj = true;
				rect->setFillColor(_getColor(ACTBUT));
			}
			
			return true;
		
		}
		
		if(!key_up){
			clickObj = false;
		}
	}

	return false;
}



namespace visualisation {
	namespace ui {

		void events(bool LMousePressed, sf::RenderWindow& win) {
			for (int i = 0; i < 16; ++i) {
				if (buttons[i]->setColor(i, LMousePressed, sf::Mouse::getPosition(win))) {
					switch (i) {
					case 0: //Fill grid
						grid.clearGrid(0);
						initSearch(grid);
						buttons[4]->setState(false);
						break;

					case 1: //Clear grid
						grid.clearGrid(1);
						initSearch(grid);
						buttons[4]->setState(false);
						break;

					case 2: //Small Noise
						grid.gridNoise(25);
						initSearch(grid);
						buttons[4]->setState(false);
						break;

					case 3: //Big Noise
						grid.gridNoise(33);
						initSearch(grid);
						buttons[4]->setState(false);
						break;

					case 4: //Start 
						initSearch(grid);
						buttons[4]->setState(true);
						break;

					case 5: //Pause
						buttons[4]->setState(false);
						break;

					case 6: //Reset
						buttons[4]->setState(false);
						initSearch(grid);
						break;

					case 7: //Move
						buttons[4]->setState(false);
						startAlg(1);
						break;

					case 8: //random
						for (int w = 0; w < grid.size.x; ++w) {
							for (int h = 0; h < grid.size.y; ++h) {
								if (grid.getState({ w, h }) == State(1)) {
									grid.randMarks();
									initSearch(grid);
									break;
								}
							}
						}
						break;


					case 9: // Show Border
						buttons[i]->setState(!buttons[i]->getState());
						break;

					case 10: //Show Searched
						buttons[i]->setState(!buttons[i]->getState());
						break;

					case 11: //Early exit
						buttons[i]->setState(!buttons[i]->getState());
						earlyExit = !earlyExit;
						break;

					case 12:
						algorithmMetod = 0;
						buttons[i]->setState(true);
						buttons[4]->setState(false);
						buttons[13]->setState(false);
						buttons[14]->setState(false);
						initSearch(grid);
						break;

					case 13:
						algorithmMetod = 1;
						buttons[i]->setState(true);
						buttons[4]->setState(false);
						buttons[12]->setState(false);
						buttons[14]->setState(false);
						initSearch(grid);
						break;

					case 14:
						algorithmMetod = 2;
						buttons[i]->setState(true);
						buttons[4]->setState(false);
						buttons[12]->setState(false);
						buttons[13]->setState(false);
						initSearch(grid);
						break;

					case 15:
						if (buttons[i]->text.getString() == "30") {
							win.setFramerateLimit(60);
							buttons[i]->text.setString("60");
						}

						else{
							win.setFramerateLimit(30);
							buttons[i]->text.setString("30");
						}
							break;
					}
				}
				

			}

			

			sizeSlider->logic(sf::Mouse::getPosition());
			animSpeedSlider->logic(sf::Mouse::getPosition());
			SoundVolumeSlider->logic(sf::Mouse::getPosition());

			sound::setVolume(SoundVolumeSlider->getValue());

			grid.size.y = static_cast<int>(ui::sizeSlider->getValue());
			grid.size.x = grid.size.y * 2;

		}

		//Initialize all texts, font, etc.
		void initUi() {

			text.setFont(font); // font is a sf::Font
			text.setStyle(sf::Text::Bold);
			sizeSlider = new Slider({ 50.0f, 880.0f }, { 1820.0f, 16.0f }, 100.0f, 1.0f, 50.0f, { 50.0f + 1820.0f / 2.0f, 880.0f});
			animSpeedSlider = new Slider({ 1630.0f, 490.0f }, { 250.0f, 15.0f }, 50.0f, 0.0f, 20.0f, { 1640.0f, 490.0f });
			animSpeedSlider->setValue(1.0f);
			
			SoundVolumeSlider = new Slider({ 1630.0f, 410.0f }, { 250.0f, 15.0f }, 50.0f, 0.0f, 100.0f, { 1755.0f, 410.0f});
			

			buttons[0] = new Button("Fill Grid", false, { 90.0f, 940.0f }, { 320.0f, 80.0f }, 35);
			buttons[1] = new Button("Clear Grid", false, { 460.0f, 940.0f }, { 320.0f, 80.0f }, 35);
			buttons[2] = new Button("Small Noise", false, { 830.0f, 940.0f }, { 320.0f, 80.0f }, 35);
			buttons[3] = new Button("Big Noise", false, { 1200.0f, 940.0f }, { 320.0f, 80.0f }, 35);

			buttons[4] = new Button("Start", false, { 1605.0f, 760.0f }, { 72.0f, 40.0f }, 21);
			buttons[5] = new Button("Pause", false, { 1685.0f, 760.0f }, { 72.0f, 40.0f }, 21);
			buttons[6] = new Button("Reset", false, { 1765.0f, 760.0f }, { 72.0f, 40.0f }, 21);
			buttons[7] = new Button("Move", false, { 1845.0f, 760.0f }, { 72.0f, 40.0f }, 21);
			buttons[8] = new Button("Random", false, { 1570.0f, 940.0f }, { 320.0f, 80.0f }, 35);

			buttons[9] = new Button("", true, {1630.0f, 700.0f }, { 30.0f, 30.0f }, 0); // Show border
			buttons[10] = new Button("", true, { 1630.0f, 650.0f }, { 30.0f, 30.0f }, 0); // Show searched
			buttons[11] = new Button("", true, { 1630.0f, 600.0f }, { 30.0f, 30.0f }, 0); // Show Early Exit

			buttons[12] = new Button("Breadth first search", true, { 1620.0f, 100.0f }, { 280.0f, 50.0f }, 23); // Breath search
			buttons[13] = new Button("Greedy flood search", false, { 1620.0f, 160.0f }, { 280.0f, 50.0f }, 23); // Greedth search
			buttons[14] = new Button("A* search", false, { 1620.0f, 220.0f }, { 280.0f, 50.0f }, 23); // A*
			buttons[15] = new Button("60", false, { 1800.0f, 530.0f }, { 50.0f, 50.0f }, 26); // Show Early Exit
			

			exitButton = new Button("Exit", false, { 1880.0f, 20.0f }, {0.0f, 0.0f }, 25); // Exit
			exitButton->rect->setFillColor(sf::Color::White);
			exitButton->text.setFillColor(_getColor(INACTBUT));
			exitButton->text.setOutlineThickness(0.2f);

			buttons[9]->rect->setOutlineThickness(4.0f);
			buttons[9]->rect->setOutlineColor(sf::Color::Black);
			buttons[10]->rect->setOutlineThickness(4.0f);
			buttons[10]->rect->setOutlineColor(sf::Color::Black);
			buttons[11]->rect->setOutlineThickness(4.0f);
			buttons[11]->rect->setOutlineColor(sf::Color::Black);

		}

		//render buttons, sliders, text
		void renderUi(sf::RenderWindow& win) {
			//win.draw(chooseAlg_text);
			for (Button* button: buttons) {
				button->draw(win);
			}

			exitButton->draw(win);
			sizeSlider->draw(win);
			animSpeedSlider->draw(win);
			SoundVolumeSlider->draw(win);

			renderText(win, "Algorithm method", { 1635.0f, 50.0f }, 1.0f, sf::Color::Black);
			renderText(win, "Grid Size", { (sizeSlider->getScrollbarPos().x + sizeSlider->size.x) / 2 - 50, 810 }, 1.3f, sf::Color::Black);
			renderText(win, "Show Border", { 1680.0f, 700.0f }, 0.9f, sf::Color::Black);
			renderText(win, "Show Searched", { 1680.0f, 650.0f }, 0.9f, sf::Color::Black);
			renderText(win, "Early Exit", { 1680.0f, 600.0f }, 0.9f, sf::Color::Black);
			renderText(win, "Animation Speed", { 1630.0f, 440.0f }, 1.0f, sf::Color::Black);
			renderText(win, "Sound Volume", { 1650.0f, 360.0f }, 1.0f, sf::Color::Black);
			renderText(win, "Framerate:", { 1630.0f, 535.0f }, 1.0f, sf::Color::Black);
		}

		void renderText(sf::RenderWindow& win,
			const std::string& string, sf::Vector2f position, float scale,
			sf::Color fillColor
		) {
			text.setString(string);
			text.setPosition(position);
			text.setScale(scale, scale);
			text.setFillColor(fillColor);

			win.draw(text);
		}

		sf::Text text;

		Button* exitButton;

		Button* buttons[16];
		Slider* sizeSlider;
		Slider* animSpeedSlider;
		Slider* SoundVolumeSlider;
	}
}