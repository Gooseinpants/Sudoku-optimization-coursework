#include "StartWindow.h"
#include "MainWindow.h"
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <time.h>
#else
#error UNSUPPORTED PLATFORM
#endif

StartWindow::StartWindow(RenderWindow* rw, string path) : AbstractWindow(rw, path)
{
	font.loadFromFile(path + "fonts/Segoe UI.ttf");
	selectBlockTexture.loadFromFile(path + "textures/block.png");
	selectBlock.setTexture(selectBlockTexture);


	startText.setFont(font);
	startText.setString("Menu:");
	startText.setFillColor(sf::Color::Black);
	startText.setCharacterSize(56);
	startText.setPosition(50, 50);


	startGameText.setFont(font);
	startGameText.setString("Start Game");
	startGameText.setFillColor(sf::Color::Black);
	startGameText.setCharacterSize(46);
	startGameText.setPosition(70, 150);

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setFillColor(sf::Color::Black);
	exitText.setCharacterSize(46);
	exitText.setPosition(70, 200);

	aboutText.setFont(font);
	aboutText.setString("Creators:\nAndrey Lyapin\nAnna Zarubina");
	aboutText.setFillColor(sf::Color::Black);
	aboutText.setCharacterSize(46);
	aboutText.setPosition(70, 500);
}

AbstractWindow* StartWindow::Render()
{
	if (Keyboard::isKeyPressed(sf::Keyboard::Down) && selectMenu != 1)
	{
		selectMenu++;
#ifdef _WIN32
		Sleep(200);
#elif __linux__
		usleep(200000);
#endif
	}
	if (Keyboard::isKeyPressed(sf::Keyboard::Up) && selectMenu != 0)
	{
		selectMenu--;
#ifdef _WIN32
		Sleep(200);
#elif __linux__
		usleep(200000);
#endif
	}

	if (Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (selectMenu == 0)
		{
#ifdef _WIN32
			Sleep(200);
#elif __linux__
			usleep(200000);
#endif
			return new MainWindow(renderWindow, path);
		}
		else
		{
			exit(0);
		}
	}



	selectBlock.setPosition(15, 150 + selectMenu * 50);

	renderWindow->draw(startText);
	renderWindow->draw(startGameText);
	renderWindow->draw(exitText);
	renderWindow->draw(aboutText);
	renderWindow->draw(selectBlock);

	return this;
}
