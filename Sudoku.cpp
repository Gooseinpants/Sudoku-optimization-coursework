#include <string>
#include <SFML/Graphics.hpp>

#include "MainWindow.h"
#include "AbstractWindow.h"
#include "GameWindow.h"
#include "engine.h"
#include "StartWindow.h"
#include "extract_filename.h"

using namespace sf;
#define WINDOW_HEIGHT 900
#define WINDOW_WIGHT 1280


std::string path = "";

int main(int __argc, char *__argv[])
{
    path = ExtractFilePath(__argv[0]);
    RenderWindow window(VideoMode(WINDOW_WIGHT, WINDOW_HEIGHT), "Sudoku");

    sudoku_cl * sudoku;
    StartWindow* startWindow = new StartWindow(&window, path);
    AbstractWindow* activeWindow = startWindow;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        activeWindow = activeWindow->Render();
        window.display();
    }

    return 0;
}