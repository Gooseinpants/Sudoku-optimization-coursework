#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AbstractWindow.h"

using namespace sf;

class MainWindow : public AbstractWindow
{
public:
	MainWindow(RenderWindow* rw, std::string path);
	AbstractWindow* Render() override;

private:
	Font font;
	Text startText, easyText, normalText, hardText;
	Texture selectBlockTexture;
	Sprite selectBlock;

	bool key_released = 1;
	int selectLevel = 0;
	int state = 0;
	int difficulty;
};

