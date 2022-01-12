#include "AbstractWindow.h"

AbstractWindow::AbstractWindow(RenderWindow* rw, std::string path)
{
	renderWindow = rw;
	this->path = path;
}
