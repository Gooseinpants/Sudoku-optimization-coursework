#pragma once
#include <SFML/Graphics.hpp>
#include <string>
//#include <iostream>

using namespace sf;

#define WINDOW_HEIGHT 900
#define WINDOW_WIGHT 1280

class AbstractWindow
{
public:
	AbstractWindow(RenderWindow* rw, std::string path);
	virtual AbstractWindow* Render() = 0;

	RenderWindow* renderWindow;
	std::string path;
};

