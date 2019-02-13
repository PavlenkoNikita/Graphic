#include "stdafx.h"
#include "StdWindow.h"

Window::Window(HINSTANCE phInstance, LPTSTR pName, LPTSTR pTitle)
{
	hInstance = phInstance;
	name			  = pName;
	title			  = pTitle;
	width			  = 400;
	height			  = 300;
	x				  = 400;
	y				  = 400;
	registerClass();
}

Window::Window(HINSTANCE phInstance)
{
	hInstance = phInstance;
	name	          = "DefaultName";
	title	          = "DefaultTitle";
	width			  = 400;
	height			  = 300;
	x				  = 400;
	y				  = 400;
	registerClass();
}

Window::Window()
{
	name = "DefaultName";
	title = "DefaultTitle";
	width = 400;
	height = 300;
	x = 400;
	y = 400;
}

void Window::setSize(unsigned short  pWidth, unsigned short  pHeight)
{
	width  = pWidth;
	height = pHeight;
}

void Window::setLocation(unsigned short  pX, unsigned short  pY)
{
	x = pX;
	y = pY;
}

int Window::run(int nCmdShow)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	if (InitInstance(hInstance, nCmdShow))
	{
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

void Window::addElement(std::string pKey, HWND pValue)
{
	mapElemets.insert(std::pair<std::string, HWND>(pKey, pValue));
}

HWND Window::getElement(std::string pKey)
{
	if (mapElemets.find(pKey) != mapElemets.end()) 
		return mapElemets[pKey];
	else                                     
		return NULL;
}

HINSTANCE Window::getHInstance()
{
	return hInstance;
}

void Window::addElements(std::vector<Element> pElement, HWND hwnd)
{	
	elements = std::vector<Element>(pElement);
	nElements = elements.size();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		HWND hElement = CreateWindowEx(
			pElement[i].dwExStyle,
			pElement[i].lpClassName,
			pElement[i].lpWindowName,
			pElement[i].dwStyle,
			pElement[i].X,
			pElement[i].Y,
			pElement[i].nWidth,
			pElement[i].nHeight,
			hwnd,
			pElement[i].hMenu,
			hInstance,
			pElement[i].lpParam
			);
		addElement(pElement[i].name, hElement);
	}
}

void Window::moveElements(int pWidth, int pHeight, int widthSettings)
{
	setSize(pWidth, pHeight);
	for (int i = 0; i < nElements; i++)
	{
		if (elements[i].lpClassName == "STATIC")
		{
			int X = pWidth - widthSettings - 5;
			int H = height;
			if (elements[i].name != "Label_Settings")
			{
				X += 10;
				H = elements[i].nHeight;
			}
			MoveWindow(
				getElement(elements[i].name),
				X,
				elements[i].Y,
				elements[i].nWidth,
				H,
				1
			);
		}
		else if (elements[i].lpClassName == "EDIT")
		{
			MoveWindow(
				getElement(elements[i].name),
				pWidth - widthSettings + 20, 
				elements[i].Y,
				elements[i].nWidth,
				elements[i].nHeight,
				1
			);

			SendMessage(
				getElement(elements[i].name),
				WM_SETTEXT,
				0,
				(LPARAM)"0.0"
			);
		}
		else if (elements[i].lpClassName == UPDOWN_CLASS)
		{
			SendMessage(
				getElement(elements[i].name),
				UDM_SETBUDDY,
				(WPARAM)getElement(elements[i-1].name),
				0
			);
			SendMessage(
				getElement(elements[i].name),
				UDM_SETRANGE,
				0,
				MAKELPARAM(100, -100));
		}
		else
		{
			MoveWindow(
				getElement(elements[i].name),
				pWidth - widthSettings,
				elements[i].Y,
				elements[i].nWidth,
				elements[i].nHeight,
				1
			);
		}
	}
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

ATOM Window::registerClass()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GLWINAPP));
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName = name;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMWINAPP));

	return RegisterClassEx(&wcex); 
}

BOOL Window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hWnd = CreateWindow(name, title, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		x, y, width, height, NULL, NULL, hInstance, NULL);
	if (hWnd)
	{
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}
	return hWnd != NULL;
}

Window::~Window()
{
}