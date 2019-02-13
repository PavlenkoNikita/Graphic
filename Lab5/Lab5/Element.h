#pragma once

struct Element
{
	LPTSTR name;
	DWORD  dwExStyle;
	LPTSTR lpClassName;
	LPTSTR lpWindowName;
	DWORD  dwStyle;
	int    X;
	int	   Y;
	int    nWidth;
	int    nHeight;
	HMENU  hMenu;
	LPVOID lpParam;

	Element(LPTSTR pName, DWORD dwExStyle, LPTSTR lpClassName, LPTSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HMENU hMenu, LPVOID lpParam);
	Element();
};

