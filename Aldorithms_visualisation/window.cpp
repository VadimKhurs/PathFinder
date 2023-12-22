#include <window.hpp>

namespace visualisation {
	
	namespace window {
		sf::RenderWindow* win = nullptr;

		void create_win(bool fullscreen) {
			if (win == nullptr) {
				win = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Algoritm visualisation", sf::Style::Fullscreen);
			}
			else {
				if (fullscreen)
					win->create(sf::VideoMode::getDesktopMode(), "Algoritm visualisation", sf::Style::Fullscreen);
				else
					win->create(sf::VideoMode::getDesktopMode(), "Algoritm visualisation", sf::Style::Default);
			}
		}

		void update()
		{
			
			//event loop
			sf::Event event;
			while (win->pollEvent(event))
			{

				bool mouseOnGrid = render::mouseOnGrid(grid);
				bool LMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

				ui::events(LMousePressed, *win);

				//Here should be a switch
				if (event.type == sf::Event::Closed)
					win->close();

				//if (event.type == sf::Event::MouseWheelMoved)
				 //{
					// if(event.mouseWheel.delta > 0 && )

				 //}


				else if (sf::Event::KeyPressed) {
					

					if (ui::exitButton->text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*win)))) {
						if (LMousePressed && key_up) {
							win->close();
						}
						ui::exitButton->text.setFillColor(_getColor(POINTED_BUT));
					}

					else
						ui::exitButton->text.setFillColor(sf::Color::Black);

					if (mouseOnGrid && sf::Mouse::isButtonPressed) {
						sf::Vector2i blockTile = render::mouseOnTile(grid);

						if (LMousePressed) {
							if (blockTile == grid.start_mark) {
								grid.start_block = false;

							}

							else if (blockTile == grid.end_mark) {
								grid.end_block = false;
							}

							if (!grid.start_block) {
								grid.start_mark = blockTile;
								initSearch(grid);
							}

							else if (!grid.end_block) {
								grid.end_mark = blockTile;

								if (grid.algorithm_bool)
									findPath(grid);

							}
						}

						if (grid.start_block && grid.end_block) {
							if (LMousePressed)
								grid.setState(blockTile, 0);

							if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
								grid.setState(blockTile, 1);
						}
					}



					if (!LMousePressed || !mouseOnGrid) {
						grid.start_block = true;
						grid.end_block = true;

					}

					grid.rectSize.x = (field.y / grid.size.y) - BORDER_WIDTH;
					grid.rectSize.y = grid.rectSize.x;

				}

			    if (LMousePressed && key_up) {
					key_up = false;
					
				}

				
				
			}
			//ui::buttons[4]->setState(startAlg(ui::animSpeedSlider->getValue()));
			if (ui::buttons[4]->getState()) {
				if (startAlg(ui::animSpeedSlider->getValue())) ui::buttons[4]->setState(false);
			} 

			win->clear(sf::Color::White);
		}

	}


	
	namespace render {
		sf::RectangleShape rect;

		sf::Vector2i mouseOnTile(const Grid& grid) {
			return {static_cast<int>(sf::Mouse::getPosition().x / (grid.rectSize.x + BORDER_WIDTH)), 
				static_cast<int>(sf::Mouse::getPosition().y / (grid.rectSize.y + BORDER_WIDTH)) };
		}
		
		bool mouseOnGrid(Grid& grid) {
			return(sf::Mouse::getPosition().x < field.x && sf::Mouse::getPosition().y < field.y);
		}


		void renderGrid (const Grid& grid) {
			
			rect.setSize(grid.rectSize);
			rect.setFillColor(sf::Color(255, 255, 255));
			rect.setOutlineThickness(BORDER_WIDTH);
			rect.setOutlineColor(sf::Color(0, 0, 0));

			float square_width = grid.rectSize.x + BORDER_WIDTH; 
			float square_height = grid.rectSize.y + BORDER_WIDTH;
			
			for (int w = 0; w < grid.size.x; ++w) {
				for (int h = 0; h < grid.size.y; ++h) {
					State isStateCurrent = grid.getState({ w, h });

					switch (isStateCurrent) {
						case 0:
							rect.setFillColor(sf::Color(30, 30, 30));
							break;
						case 1:
							rect.setFillColor(sf::Color(255, 255, 255));
							break;
					}

					rect.setPosition(square_width * w, square_height * h);
					

					window::win->draw(rect);
				}
			}
			
			//бпелеммн

			rect.setFillColor(sf::Color(30, 30, 155));
			if (ui::buttons[10]->getState()) {
				for (int i = 0; i < grid.searched.size(); ++i) {
					if (grid.validPos(grid.searched[i]) && grid.getState(grid.searched[i]) == State(1)) {
						rect.setPosition(square_width * grid.searched[i].x, square_height * grid.searched[i].y);
						window::win->draw(rect);
					}
				}
			}

			if (ui::buttons[9]->getState()) {
			
				rect.setFillColor(sf::Color(0, 0, 255));
			
				std::queue<sf::Vector2i> tmp_q = grid.border;

				while(!tmp_q.empty()){
					sf::Vector2i pos = tmp_q.front();
					tmp_q.pop();

					if (grid.validPos(pos) && grid.getState(pos) == State(1)) {
						rect.setPosition(square_width * pos.x, square_height * pos.y);
						window::win->draw(rect);
				
					}

				}
			

				std::priority_queue<SearchQueue> tmp_p = grid.priority_border;

				while (!tmp_p.empty()) {
					sf::Vector2i pos = tmp_p.top().pos;
					tmp_p.pop();
					if (grid.validPos(pos) && grid.getState(pos) == State(1)) {
						rect.setPosition(square_width * pos.x, square_height * pos.y);
						window::win->draw(rect);
					}
				}

				
			}

			rect.setFillColor(sf::Color(139, 0, 255));

			for (int i = 0; i < grid.path.size(); ++i) {
				sf::Vector2i pos = grid.path[i];

				if (grid.validPos(pos) && grid.getState(pos) == State(1)) {
					rect.setPosition(square_width * pos.x, square_height * pos.y);
					window::win->draw(rect);

				}
			}
			//бпелеммн
			
			//draw start_mark
			if (grid.validPos(grid.start_mark)){
				rect.setPosition(square_width * grid.start_mark.x, square_height * grid.start_mark.y);
				rect.setFillColor(sf::Color(0, 255, 0));

				window::win->draw(rect);
			}

			//draw start_mark
			if (grid.validPos(grid.end_mark)) {
			
				rect.setPosition(square_width * grid.end_mark.x, square_height * grid.end_mark.y);
				rect.setFillColor(sf::Color(255, 0, 0));

				window::win->draw(rect);
			}
		}

		void render() {
			renderGrid(grid);
			ui::renderUi(*window::win);

		}
	}
}


