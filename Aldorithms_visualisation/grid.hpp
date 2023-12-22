#pragma once
#include <resource.hpp>

extern bool key_up;

sf::Color _getColor(MYCOLORS color);

extern sf::Font font;

namespace visualisation {
	

	typedef int State;

	//Hash function for unordered map
	struct HashFunc {
		size_t operator()(const sf::Vector2i& pos) const;
	};

	//Used as an operator for queues to sort an array
	struct SearchQueue {
		sf::Vector2i pos;
		float cost;

		SearchQueue();
		SearchQueue(sf::Vector2i pos, int cost);

		bool operator>(const SearchQueue& tile) const;

		bool operator<(const SearchQueue& tile) const;
	};


	class Grid {
	public:
		//Start and end position 
		sf::Vector2i start_mark;
		sf::Vector2i end_mark;
		//Size needs to render grid
		sf::Vector2i size;

		//Block size
		sf::Vector2f rectSize{RECSIZE, RECSIZE};

		//Array with searched area
		std::vector <sf::Vector2i> searched;

		//breath_first container
		std::queue<sf::Vector2i> border;
		//greed_search container and A* costMap
		std::priority_queue<SearchQueue> priority_border;
		std::unordered_map<sf::Vector2i, float, HashFunc>costMap;

		//Containers to create a path
		std::unordered_map<sf::Vector2i, sf::Vector2i, HashFunc> pathMap;
		std::vector <sf::Vector2i> path;

		//Start and end marks clicked?
		bool start_block = true; 
		bool end_block = true;	// Same

		//Is the algorithm completed?
		bool algorithm_bool = false; 
		
		Grid();
		~Grid();

		void create(sf::Vector2i grid_size);

		//Set block state in grid(0 or 1)
		void setState(sf::Vector2i pos, State state);

		//Get position in array represented from 2d array in 1d
		int getArrayPos(sf::Vector2i pos) const;

		//Get grid size(no render limit)
		sf::Vector2i getRealSize() const;

		//Fill grid and set type
		void clearGrid(State type);

		//Generate noise
		void gridNoise(int probability);

		void randMarks();

		//Check position of anything(true - if position in grid)
		bool validPos(sf::Vector2i pos) const;

		//Check block state
		State getState(sf::Vector2i pos) const;

	private:
		//Array of grid's blocks states
		State* states;
		//Grid size(no render limit)
		sf::Vector2i real_size;
	};


	extern Grid grid;

	//Distance between 2 points
	int manhattan_distance(sf::Vector2i pos, sf::Vector2i pos2);

}