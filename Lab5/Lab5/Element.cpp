#pragma once
#include "stdafx.h"

Element::Element(LPTSTR pName, DWORD pExStyle, LPTSTR pClassName, LPTSTR pWindowName, DWORD pStyle, int pX, int pY, int pWidth, int pHeight, HMENU pMenu, LPVOID pParam)
{
	name = pName;
	dwExStyle = pExStyle;
	lpClassName = pClassName;
	lpWindowName = pWindowName;
	dwStyle = pStyle;
	X = pX;
	Y = pY;
	nWidth = pWidth;
	nHeight = pHeight;
	hMenu = pMenu;
	lpParam = pParam;
}

Element::Element()
{
	ZeroMemory(this, sizeof(this));
}