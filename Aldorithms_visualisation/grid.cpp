#include <grid.hpp>
bool key_up = true;





sf::Color _getColor(MYCOLORS color) {
	switch (color) {

	case INACTBUT:
		return sf::Color(32, 33, 36);

	case ACTBUT:
		return sf::Color(0, 0, 255); //54, 70, 97

	case POINTED_BUT:
		return sf::Color(48, 49, 53);

	}
	return sf::Color(0, 0, 0);
}



namespace visualisation {
	


	size_t HashFunc::operator()(const sf::Vector2i& pos) const {
		return size_t(pos.x) << 32 | pos.y;
	}

	SearchQueue::SearchQueue() :cost(0) {}

	SearchQueue::SearchQueue(sf::Vector2i pos, int cost) : pos(pos), cost(static_cast<float>(cost)) {}

	bool SearchQueue::operator>(const SearchQueue& tile) const
	{
		return cost < tile.cost;
	}

	bool SearchQueue::operator<(const SearchQueue& tile) const
	{
		return cost > tile.cost;
	}



	Grid grid;

	Grid::Grid() : start_mark({ 0,0 }), states(nullptr), end_mark({ 10,10 }) {}

	Grid::~Grid() {
		delete[] states;
	}



	void Grid::create(sf::Vector2i size) {
		if (states != nullptr) delete states;

		states = new State[size.x * size.y];

		real_size = size;

		this->size = size;

		clearGrid(State(1));

		this->size = { size.x / 2, size.y / 2 };
	}

	void Grid::setState(sf::Vector2i pos, State state) {

		if (validPos(pos)) {
			states[getArrayPos(pos)] = state;
		}
	}

	int Grid::getArrayPos(sf::Vector2i pos) const {
		return getRealSize().x * pos.y + pos.x;
	}

	sf::Vector2i Grid::getRealSize() const {
		return real_size;
	}

	bool Grid::validPos(sf::Vector2i pos) const {
		return (pos.x >= 0 && pos.x < size.x
			&& pos.y >= 0 && pos.y < size.y);
	}

	State Grid::getState(sf::Vector2i pos) const {
		if (validPos(pos))
			return states[getArrayPos(pos)];

		return State(-1);
	}

	void Grid::clearGrid(State type) {
		for (int w = 0; w < size.x; ++w) {
			for (int h = 0; h < size.y; ++h) {
				setState({ w, h }, type);
			}
		}

		//stop searching 

	}

	void Grid::gridNoise(int probability) {

		clearGrid(1);

		for (int w = 0; w < size.x; ++w) {
			for (int h = 0; h < size.y; ++h) {
				sf::Vector2i pos = { w, h };

				if (start_mark == pos || end_mark == pos)
					continue;

				if (rand() % 100 < probability)
					setState(pos, 0);
			}
		}

	}

	void Grid::randMarks() {
		start_mark = { rand() % size.x, rand() % size.y };
		while (getState(start_mark) == State(0)) {
			start_mark = { rand() % size.x, rand() % size.y };
		}
			
		end_mark = { rand() % size.x, rand() % size.y };
		while (getState(end_mark) == State(0)) {
			end_mark = { rand() % size.x, rand() % size.y };
		}
	};


	int manhattan_distance(sf::Vector2i pos, sf::Vector2i pos2)
	{
		return std::abs(pos.x - pos2.x) + std::abs(pos.y - pos2.y);
	}
}