#include "StdWindow.h"
#include "stdafx.h"

Window mainWindow;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LPTSTR NameClass   = "MainWindow";
	LPTSTR TitleWindow = "Lab5";
	int Width		   = 600;
	int Height		   = 500;
	int x			   = 650;
	int y              = 250;
    mainWindow         = Window(hInstance, NameClass, TitleWindow);
	
	mainWindow.setSize(Width, Height);
	mainWindow.setLocation(x, y);
	return mainWindow.run(nCmdShow);
}
