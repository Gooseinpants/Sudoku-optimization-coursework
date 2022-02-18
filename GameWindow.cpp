#include "GameWindow.h"
#include "StartWindow.h"

GameWindow::GameWindow(int difficulty, int size, RenderWindow* rw, std::string path) : AbstractWindow(rw, path)
{
	this->difficulty = difficulty;
	this->size = size;
	clock_t start_gen = clock();
	sudoku = new sudoku_cl(size, difficulty + 1);
	clock_t finished_gen = clock();
	double time_gen = (double)((finished_gen-start_gen)/CLOCKS_PER_SEC);
	printf("%f", time_gen);
	font.loadFromFile(path + "fonts/Segoe UI.ttf");
	blockTexture.loadFromFile(path + "textures/block.png");

	startText.setFont(font);
	startText.setFillColor(sf::Color::Black);
	startText.setCharacterSize(48);
	startText.setPosition((WINDOW_WIGHT / 2) - 150, 50);


	//�������� ��������
	for (int i = 0; i < size * size; i++)
	{
		vector<Sprite> row;
		for (int j = 0; j < size * size; j++)
		{
			Sprite tmp;
			tmp.setTexture(blockTexture);
			row.push_back(tmp);
		}
		field.push_back(row);
	}
	//�������� ������
	for (int i = 0; i < size * size; i++)
	{
		vector<Text> row;
		for (int j = 0; j < size * size; j++)
		{
			Text tmp;
			tmp.setFont(font);
			char number_on_board;
			if (sudoku->board[i + 1][j + 1] > 9)
			{
				number_on_board = 55 + sudoku->board[i + 1][j + 1];
			}
			else number_on_board = 48 + sudoku->board[i + 1][j + 1];
			tmp.setString(number_on_board);
			if (sudoku->board[i + 1][j + 1]) tmp.setFillColor(sf::Color::Black);
			else tmp.setFillColor(sf::Color::Blue);
			tmp.setCharacterSize(30);
			row.push_back(tmp);
		}
		fieldText.push_back(row);
	}

	int offsetX = 0;
	int offsetY = 0;

	for (int y = 0; y < size * size; y++)
	{
		if (y % size == 0)
		{
			offsetY++;
		}
		for (int x = 0; x < size * size; x++)
		{
			if (x % size == 0)
			{
				offsetX++;
			}
			field[x][y].setPosition(25 + offsetX + 48 * (x), 25 + offsetY + 48 * (y));
			fieldText[x][y].setPosition(40 + offsetX + 48 * (x), 35 + offsetY + 48 * (y));
		}
		offsetX = 0;
	}

}

AbstractWindow* GameWindow::Render()
{
	if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return new StartWindow(renderWindow, path);
	}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		selectBlockPos = nullptr;
		Vector2i position = Mouse::getPosition(*renderWindow);
		auto translated_pos = renderWindow->mapPixelToCoords(position);

		for (int i = 0; i < size * size; i++)
		{
			for (int j = 0; j < size * size; j++)
			{
				if (field[i][j].getGlobalBounds().contains(translated_pos))
				{
					bool flag = false;
					for (int k = 0; k < notSetBlocks.size(); k++)
					{
						if (notSetBlocks[k].x == i && notSetBlocks[k].y == j)
						{
							flag = true;
							break;
						}
					}
					if (!flag)
					{
						selectBlockPos = new Vector2i(i, j);
						field[i][j].setColor(Color::Magenta);
					}
				}
				else
				{
					field[i][j].setColor(Color::White);
				}
			}
		}
	}

	if (selectBlockPos != nullptr && sudoku->change[selectBlockPos->x + 1][selectBlockPos->y + 1])
	{
		switch (size)
		{

		case 4:
			if (Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 10;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "A");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 11;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "B");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 12;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "C");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 13;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "D");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 14;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "E");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 15;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "F");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 16;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "G");
			}
		case 3:
			if (Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 5;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "5");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num6))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 6;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "6");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num7))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 7;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "7");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num8))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 8;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "8");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num9))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 9;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "9");
			}
		case 2:
			if (Keyboard::isKeyPressed(sf::Keyboard::Num0) || Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 0;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "0");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 1;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "1");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 2;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "2");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 3;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "3");
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				sudoku->board[selectBlockPos->x + 1][selectBlockPos->y + 1] = 4;
				SetBlockValue(selectBlockPos->x, selectBlockPos->y, "4");
			}
			break;
		}
		if (sudoku->is_solved())
			Win();
	}


	for (int i = 0; i < size * size; i++)
	{
		for (int j = 0; j < size * size; j++)
		{
			renderWindow->draw(field[i][j]);
			if (fieldText[i][j].getString() != "0")
			{
				renderWindow->draw(fieldText[i][j]);
			}
		}
	}

	renderWindow->draw(startText);

	return this;
}

void GameWindow::SetBlockValue(int x, int y, string value)
{
	fieldText[x][y].setString(value);
}

void GameWindow::Win()
{
	startText.setString("WIN");
}
