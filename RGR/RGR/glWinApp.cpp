#include "stdafx.h"
#include "StdWindow.h"

Scene scene;

GLfloat angleBC = 0, angleOC = 0, angleAC = 25, angleYOZ = 0;
GLfloat sizeA = 0.46;
GLfloat S = -sizeA;

//Mouse
GLfloat X0 = 0, Y0 = 0, m = 1;
GLfloat angleX = 0, angleY = 0;
GLboolean canMove = false;

GLfloat light0_diffuse[] = { 1, 1, 1, 1 };
GLfloat light0_direction[] = { 0.0, 0.0, 1, 0.0 };
GLfloat ambient[4] = { 0.3, 0.3, 0.3, 1 };
GLfloat specular[4] = { 1, 1, 1, 1 };

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER);
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;

	HDC hDC = GetDC(hwnd);

	int n = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, n, &pfd);
	wglMakeCurrent(hDC, wglCreateContext(hDC));

	glClearColor(0.50f, 0.50f, 0.50f, 1.0f);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	const GLuint countTextures = 13;
	HBITMAP hBMP;
	BITMAP  BMP_textures;
	GLuint  textureIDs[countTextures];
	LPTSTR  nameFiles[countTextures] =
	{
	"metal.bmp",
	"lightGreen.bmp",
	"lightGreen.bmp",
	"tree.bmp",
	"Red.bmp",
	"Red.bmp",
	"lightGreen.bmp",
	"lightGreen.bmp",
	"tree.bmp",
	"tree.bmp",
	"lightGreen.bmp",
	"lightGreen.bmp",
	"lightGreen.bmp"
	};

	glGenTextures(countTextures, textureIDs);
	for (int i = 0; i < countTextures; i++)
	{
		hBMP = (HBITMAP)LoadImage(NULL, nameFiles[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBMP, sizeof(BMP_textures), (LPVOID)&BMP_textures);

		glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		gluBuild2DMipmaps(
			GL_TEXTURE_2D, GL_RGBA,
			BMP_textures.bmWidth, BMP_textures.bmHeight,
			GL_BGR_EXT,	GL_UNSIGNED_BYTE,
			BMP_textures.bmBits
		);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	scene.bindTexturesToScheme(textureIDs);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	return TRUE;
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
	wglMakeCurrent(0, 0);
	wglDeleteContext(wglGetCurrentContext());
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);



	RECT r;
	GetClientRect(hwnd, &r);
	scene.setViewPort(r);

	//Mouse turns
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	
		glScalef(m, m, m);

	scene.setParamsToScheme(angleYOZ, angleAC, S);
	scene.draw();

	SwapBuffers(wglGetCurrentDC());
	EndPaint(hwnd, &ps);
}

void OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	switch (vk)
	{
	case 68: //A
		angleYOZ--;
		if (angleYOZ < -360) angleYOZ += 360;
		break;
	case 65: //D
		angleYOZ++;
		if (angleYOZ > 360) angleYOZ -= 360;
		break;
	case 38: //arrow up
		if (S <= 0.86) 	S += 0.01;
		break;
	case 40: //arrow down
		if (S >= -0.86) S -= 0.01;
		break;
	case 39: //arrow left
		angleAC--;
		if (angleAC < -360) angleAC += 360;
		break;
	case 37: //arrow right
		angleAC++;
		if (angleAC > 360) angleAC -= 360;
		break;
	}
	InvalidateRect(hwnd, NULL, true);
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (canMove)
	{
		angleX += (GLfloat)(y - Y0) / 2.0;
		angleY += (GLfloat)(x - X0) / 2.0;
		X0 = x;
		Y0 = y;
		InvalidateRect(hwnd, NULL, true);
	}
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	canMove = true;
	X0 = x;
	Y0 = y;
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	canMove = false;
}

void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys)
{
	m += (-zDelta / 1000.0);
	if (m < 0.6) m = 0.6;
	if (m > 1.2)   m = 1.2;
	InvalidateRect(hwnd, NULL, true);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_KEYDOWN, OnKeyDown);
		HANDLE_MSG(hWnd, WM_MOUSEWHEEL, OnMouseWheel);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

