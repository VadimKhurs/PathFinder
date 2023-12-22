#include <path.hpp>



namespace visualisation {

	sf::Vector2i PathPoint;

	void initSearch(Grid& grid) {
		
		clearSearch(grid);
		
		grid.algorithm_bool = false;
		
		grid.border.push(grid.start_mark);
		grid.priority_border.push(SearchQueue(grid.start_mark, manhattan_distance(grid.start_mark, grid.end_mark)));
		grid.costMap[grid.start_mark] = 0;
	}

	void clearSearch(Grid& grid) {
		while(!grid.searched.empty())
			grid.searched.pop_back();
		

		while (!grid.border.empty())
			grid.border.pop();

		while (!grid.priority_border.empty())
			grid.priority_border.pop();
		
		while (!grid.path.empty())
			grid.path.pop_back();

		while (!grid.pathMap.empty())
			grid.pathMap.clear();

		while (!grid.costMap.empty())
			grid.costMap.clear();

			
	}



	bool breadth_search(Grid& grid) {
		
		if (!grid.border.empty()) {
			sf::Vector2i currentPos = grid.border.front();

			PathPoint = currentPos;

			if (currentPos == grid.end_mark && !earlyExit) { //And exit by player
				findPath(grid);
				return true;
			}
				
			grid.border.pop();

			for (int neighbour = 0; neighbour < 4; ++neighbour) {
				sf::Vector2i pos = currentPos;

				//copy past
				if (neighbour % 2 == 0)
					pos.y += neighbour == 0 ? -1 : 1;
				else
					pos.x += neighbour == 1 ? 1 : -1;

				if ((grid.validPos(pos) && grid.getState(pos) != 0) && 
					(std::find(grid.searched.begin(), grid.searched.end(), pos) == grid.searched.end()) )
				{
					grid.border.push(pos);
					grid.searched.push_back(pos);

					grid.pathMap[pos] = currentPos;
				}

			}
		
			return false;
		}

		findPath(grid);
		return true;
	}

	bool greed_search(Grid& grid)
	{
		if (!grid.priority_border.empty()) {

			sf::Vector2i currentPos = grid.priority_border.top().pos;

			PathPoint = currentPos;

			if (currentPos == grid.end_mark && !earlyExit) { // And Player exit
				findPath(grid);
				return true;
			}

			grid.priority_border.pop();

			for (int neighbour = 0; neighbour < 4; ++neighbour) {
				sf::Vector2i pos = currentPos;

				//copy past
				if (neighbour % 2 == 0)
					pos.y += neighbour == 0 ? -1 : 1;
				else
					pos.x += neighbour == 1 ? 1 : -1;

				if ((grid.validPos(pos) && grid.getState(pos) != 0) &&
					(std::find(grid.searched.begin(), grid.searched.end(), pos) == grid.searched.end()))
				{
					grid.priority_border.push(SearchQueue(pos, manhattan_distance(pos, grid.end_mark)));
					grid.searched.push_back(pos);
					grid.pathMap[pos] = currentPos;
				}
			}

			return false;
		}

		findPath(grid);
		return true;
	}

	bool AStar_search(Grid& grid)
	{
		if (!grid.priority_border.empty()) {

			sf::Vector2i currentPos = grid.priority_border.top().pos;
			
			PathPoint = currentPos;

			if (currentPos == grid.end_mark && !earlyExit) { // player exit
				findPath(grid);
				return true;
			}

			grid.priority_border.pop();

			float cost = grid.costMap[currentPos] + 1.0f;

			for (int neighbour = 0; neighbour < 4; ++neighbour) {
				sf::Vector2i pos = currentPos;

				//copy past
				if (neighbour % 2 == 0)
					pos.y += neighbour == 0 ? -1 : 1;
				else
					pos.x += neighbour == 1 ? 1 : -1;
				if ((grid.validPos(pos) && grid.getState(pos) != 0) && 
					(grid.costMap.count(pos) == 0 || grid.costMap[pos] > cost))
				{
					grid.priority_border.push(SearchQueue(pos, static_cast<int>(cost + manhattan_distance(pos, grid.end_mark) * 1.4f)));
					grid.searched.push_back(pos);
					grid.costMap[pos] = cost;
					grid.pathMap[pos] = currentPos;
				}
			}

			return false;
		}

		findPath(grid);
		return true;
	}

	void findPath(Grid& grid) {
		sf::Vector2i current_pos = grid.end_mark;
		sf::Vector2i previous_pos = sf::Vector2i{ -1, -1 };

		grid.path.clear();
		if (grid.pathMap.count(current_pos) != 0) {
			while(current_pos != grid.start_mark){
				grid.path.push_back(current_pos);

				current_pos = grid.pathMap[current_pos];

				if (current_pos == previous_pos) {
					grid.path.clear();
					return;
				}
				
				previous_pos = current_pos;
			}
			grid.path.push_back(current_pos);
		}
	}

	bool startAlg(float animSpeed)
	{
		ticks += animSpeed;
		if (ticks >= 1) {
			ticks = 0;
			while (animSpeed-- > 0) {
				switch (algorithmMetod) {
					case 0:
						grid.algorithm_bool = breadth_search(grid);
						break;

					case 1:
						grid.algorithm_bool = greed_search(grid);
						break;

					case 2:
						grid.algorithm_bool = AStar_search(grid);						
						break;

					
				}

				
			}

			sound::playSound(static_cast<float>(manhattan_distance(PathPoint, grid.end_mark)));
			return grid.algorithm_bool;
		}

		return false;
	}

}