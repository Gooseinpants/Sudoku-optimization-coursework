#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "AbstractWindow.h"
#include "engine.h"
#include <vector>

using namespace sf;
using namespace std;
class GameWindow : public AbstractWindow
{
public:
	GameWindow(int difficulty, int size, RenderWindow* rw, string path);
	AbstractWindow* Render() override;
	void FillStartField(vector<vector<int> > values);
	void FillField(vector<vector<int> > values);
	void SetBlockValue(int x, int y, string value);
	void Win();
	sudoku_cl* sudoku;
private:
	int difficulty;
	int size;
	Font font;
	Text startText;
	Texture blockTexture;
	vector<vector<Sprite> > field;
	vector<vector<Text> > fieldText;
	vector<Vector2i> notSetBlocks;
	Vector2i* selectBlockPos = nullptr;
};

