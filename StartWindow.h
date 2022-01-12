#pragma once

#include <string>
#include "AbstractWindow.h"

using namespace sf;
using namespace std;

class StartWindow : public AbstractWindow
{
public:
	StartWindow(RenderWindow* rw, string path);
	AbstractWindow* Render() override;

private:
	Font font;
	Text startText, startGameText, exitText, aboutText;
	Texture selectBlockTexture;
	Sprite selectBlock;

	int selectMenu = 0;
};

