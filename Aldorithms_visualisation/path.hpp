#pragma once
#include <Slider.hpp>
#include <sound.hpp>

namespace visualisation {
	//extern sf::Vector2i focusPoint;
	
	//Initialize all for search
	void initSearch(Grid& grid);

	//Clear all containers for search
	void clearSearch(Grid& grid);


	bool breadth_search(Grid& grid);  

	bool greed_search(Grid& grid);

	bool AStar_search(Grid& grid);

	//Find the path after completing the algorithm
	void findPath(Grid& grid);

	bool startAlg(float animSpeed);
}
