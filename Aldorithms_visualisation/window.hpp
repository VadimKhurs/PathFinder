#pragma once
#include <ui.hpp>
namespace visualisation {
	namespace window {
		extern sf::RenderWindow* win;

		//Create a window with selected size
		void create_win(bool fullscreen);

		//Update events
		void update();
	}

	namespace render{
		//Create rectangle to draw all blocks
		extern sf::RectangleShape rect;

		
		//Check mouse position in 2d grid 
		sf::Vector2i mouseOnTile(const Grid& grid);

		//Is mouse inside grid
		bool mouseOnGrid(Grid& grid);

		//render grid
		void renderGrid(const Grid& grid);

		void render();
		
		
		
	
		
	
	}

	

}
