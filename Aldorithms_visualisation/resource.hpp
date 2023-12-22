#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <vector>
#include <Windows.h>
//#include <iostream>
#include <unordered_map>

//Временно

enum MYCOLORS {
	INACTBUT = 1,
	ACTBUT,
	POINTED_BUT
};

const float BORDER_WIDTH = 3.0f;
const float RECSIZE = 13.0f;


const int width = 100;
const int height = 50;
const sf::Vector2i grid_sizes = { width, height };

const sf::Vector2f field = { width * (RECSIZE + BORDER_WIDTH), height * (RECSIZE + BORDER_WIDTH) };

extern sf::Vector2i PathPoint;
extern float ticks;
extern bool earlyExit;
extern int algorithmMetod;
