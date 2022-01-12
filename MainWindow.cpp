#include "MainWindow.h"
#include "GameWindow.h"
#include "StartWindow.h"
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <time.h>
#else
#error UNSUPPORTED PLATFORM
#endif



MainWindow::MainWindow(RenderWindow* rw, std::string path) : AbstractWindow(rw, path)
{
	font.loadFromFile(path + "fonts/Segoe UI.ttf");

	selectBlockTexture.loadFromFile(path + "textures/block.png");
	selectBlock.setTexture(selectBlockTexture);

	startText.setFont(font);
	startText.setString("Select difficulty");
	startText.setFillColor(sf::Color::Black);
	startText.setCharacterSize(48);
	startText.setPosition((WINDOW_WIGHT / 2) - 150, 50);

	easyText.setFont(font);
	easyText.setString("EASY");
	easyText.setFillColor(sf::Color::Black);
	easyText.setCharacterSize(56);
	easyText.setPosition(100, WINDOW_HEIGHT / 2);

	normalText.setFont(font);
	normalText.setString("NORMAL");
	normalText.setFillColor(sf::Color::Black);
	normalText.setCharacterSize(56);
	normalText.setPosition(100, WINDOW_HEIGHT / 2 + 100);

	hardText.setFont(font);
	hardText.setString("HARD");
	hardText.setFillColor(sf::Color::Black);
	hardText.setCharacterSize(56);
	hardText.setPosition(100, WINDOW_HEIGHT / 2 + 200);
}


AbstractWindow* MainWindow::Render()
{
	if ((Keyboard::isKeyPressed(sf::Keyboard::Escape) || Keyboard::isKeyPressed(sf::Keyboard::BackSpace)))
	{
		if (state == 0)
			return new StartWindow(renderWindow, path);
		difficulty = 0;

		startText.setString("Select difficulty");
		easyText.setString("EASY");
		normalText.setString("NORMAL");
		hardText.setString("HARD");

		selectLevel = 0;
		state = 0;
		#ifdef _WIN32
		Sleep(200);
		#elif __linux__
		usleep(200000);
		#endif
	}
	if (Keyboard::isKeyPressed(sf::Keyboard::Down) && selectLevel != 2)
	{
		selectLevel++;
		#ifdef _WIN32
		Sleep(200);
		#elif __linux__
		usleep(200000);
		#endif
	}
	if (Keyboard::isKeyPressed(sf::Keyboard::Up) && selectLevel != 0)
	{
		selectLevel--;
		#ifdef _WIN32
		Sleep(200);
		#elif __linux__
		usleep(200000);
		#endif
	}

	if (Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (state == 0)
		{
			difficulty = selectLevel;
			startText.setString("Select size");
			easyText.setString("2x2");
			normalText.setString("3x3");
			hardText.setString("4x4");
			
			selectLevel = 0;
			state++;
		}
		else 
		{
			int fieldSize = 0;
			if (selectLevel == 0)
			{
				fieldSize = 2;
			} else if (selectLevel == 1)
			{
				fieldSize = 3;
			}
			else if (selectLevel == 2)
			{
				fieldSize = 4;
			}
			return new GameWindow(difficulty, fieldSize, renderWindow, path);
		}
		#ifdef _WIN32
		Sleep(200);
		#elif __linux__
		usleep(200000);
		#endif
	}


	selectBlock.setPosition(25, WINDOW_HEIGHT / 2 + selectLevel * 100);

	renderWindow->draw(selectBlock);
	renderWindow->draw(startText);
	renderWindow->draw(easyText);
	renderWindow->draw(normalText);
	renderWindow->draw(hardText);

	return this;
}
