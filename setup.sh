g++ -O2 -c *.cpp
g++ -O2 Sudoku.o MainWindow.o GameWindow.o AbstractWindow.o engine.o StartWindow.o -o Sudoku -lsfml-graphics -lsfml-window -lsfml-system

