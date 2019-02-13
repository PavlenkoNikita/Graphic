#include "stdafx.h"
#include "StdWindow.h"

Picture			     windowPicture;
GLint			     nElements = 18;
std::vector<Element> elemetsForm(nElements);
GLint				 FontID = 0;
GLint				 locationX;
GLint				 widthSettings = 100;
std::vector<GLdouble>   equationCoefficients(4, 0);
GLboolean            canClip = false;
const GLuint countTextures = 3;
//Mouse
GLboolean			canMove = false;
GLint				X0 = 0;
GLint				Y0 = 0;
GLdouble			ax = 0;
GLdouble			ay = 0;
GLdouble			m = 1;

int LoadWindowDefaultFont()
{
	int id = glGenLists(256);
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, id);
	return id;
}

void OutText(LPCSTR str, double x, double y, double z = 0)
{
	glRasterPos3d(x, y, z);
	glListBase(FontID);
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, &str[0]);
}

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

	FontID = LoadWindowDefaultFont();

	glClearColor(0.39f, 0.47f, 0.59f, 1.0f);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	HBITMAP hBMP;
	BITMAP BMP_textures[countTextures];
	GLuint  textureIDs[countTextures];
	LPTSTR nameFiles[countTextures] =
	{ "metal.bmp" ,
	"cloth.bmp",
	"water.bmp" };
	glGenTextures(countTextures, textureIDs);
	for (int i = 0; i < countTextures; i++)
	{
		hBMP = (HBITMAP)LoadImage(NULL, (LPTSTR)nameFiles[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBMP, sizeof(BMP_textures[i]), (LPVOID)&BMP_textures[i]);

		glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			GL_RGB,
			BMP_textures[i].bmWidth,
			BMP_textures[i].bmHeight,
			GL_BGR_EXT,
			GL_UNSIGNED_BYTE,
			BMP_textures[i].bmBits
		);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	windowPicture.addTexture(textureIDs);

	std::vector<GLfloat> positionsObjects[3];
	positionsObjects[0] = std::vector<GLfloat>{ 4, -2, -3 };
	positionsObjects[1] = std::vector<GLfloat>{ 2.5, 3, 3 };
	positionsObjects[2] = std::vector<GLfloat>{ -2.5, 3.5, -3.5 };
	windowPicture.setPositionPrimitives(positionsObjects);

	windowPicture.initialization();

	RECT rcW;
	GetClientRect(hwnd, &rcW);
	locationX = rcW.right - widthSettings;

	elemetsForm[0] = Element("Label_Settings", 0, "STATIC", "", WS_CHILD | WS_VISIBLE, locationX - 5, 0, 105, rcW.bottom, (HMENU)17, NULL);
	elemetsForm[1] = Element("CheckBox_ClipPlane", 0, "BUTTON", "Clip plane", BS_CHECKBOX | WS_CHILD | WS_VISIBLE, locationX, 10, 100, 20, (HMENU)1, NULL);
	elemetsForm[2] = Element("Label_A", 0, "STATIC", "A", WS_CHILD | WS_VISIBLE, locationX + 5, 40, 10, 20, (HMENU)2, NULL);
	elemetsForm[3] = Element("Edit_A", 0, "EDIT", 0, WS_CHILD | WS_VISIBLE | WS_BORDER, locationX + 20, 40, 70, 20, (HMENU)3, NULL);
	elemetsForm[4] = Element("UpDown_A", WS_EX_WINDOWEDGE, UPDOWN_CLASS, 0, UDS_ALIGNRIGHT | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE, locationX, 40, 100, 20, (HMENU)4, NULL);
	elemetsForm[5] = Element("Label_B", 0, "STATIC", "B", WS_CHILD | WS_VISIBLE, locationX + 5, 70, 10, 20, (HMENU)5, NULL);
	elemetsForm[6] = Element("Edit_B", 0, "EDIT", 0, WS_CHILD | WS_VISIBLE | WS_BORDER, locationX + 20, 70, 70, 20, (HMENU)6, NULL);
	elemetsForm[7] = Element("UpDown_B", WS_EX_WINDOWEDGE, UPDOWN_CLASS, 0, UDS_ALIGNRIGHT | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE, locationX, 70, 100, 20, (HMENU)7, NULL);
	elemetsForm[8] = Element("Label_C", 0, "STATIC", "C", WS_CHILD | WS_VISIBLE, locationX + 5, 100, 10, 20, (HMENU)8, NULL);
	elemetsForm[9] = Element("Edit_C", 0, "EDIT", 0, WS_CHILD | WS_VISIBLE | WS_BORDER, locationX + 20, 100, 70, 20, (HMENU)9, NULL);
	elemetsForm[10] = Element("UpDown_C", WS_EX_WINDOWEDGE, UPDOWN_CLASS, 0, UDS_ALIGNRIGHT | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE, locationX, 100, 100, 20, (HMENU)10, NULL);
	elemetsForm[11] = Element("Label_D", 0, "STATIC", "D", WS_CHILD | WS_VISIBLE, locationX + 5, 130, 10, 20, (HMENU)11, NULL);
	elemetsForm[12] = Element("Edit_D", 0, "EDIT", 0, WS_CHILD | WS_VISIBLE | WS_BORDER, locationX + 20, 130, 70, 20, (HMENU)12, NULL);
	elemetsForm[13] = Element("UpDown_D", WS_EX_WINDOWEDGE, UPDOWN_CLASS, 0, UDS_ALIGNRIGHT | UDS_SETBUDDYINT | WS_CHILD | WS_VISIBLE, locationX, 130, 100, 20, (HMENU)13, NULL);
	elemetsForm[14] = Element("RadioButton_Ortho", 0, "BUTTON", "Ortho", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, locationX, 160, 100, 20, (HMENU)14, NULL);
	elemetsForm[15] = Element("RadioButton_Perspective", 0, "BUTTON", "Perspective", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, locationX, 190, 100, 20, (HMENU)15, NULL);
	elemetsForm[16] = Element("RadioButton_FillMode", 0, "BUTTON", "Fill mode", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, locationX, 220, 100, 20, (HMENU)16, NULL);
	elemetsForm[17] = Element("RadioButton_LineMode", 0, "BUTTON", "Line mode", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, locationX, 250, 100, 20, (HMENU)17, NULL);

	mainWindow.addElements(elemetsForm, hwnd);

	SendMessage(mainWindow.getElement("RadioButton_Ortho"), BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(mainWindow.getElement("RadioButton_LineMode"), BM_SETCHECK, BST_CHECKED, 0);
	
	//hBMP = LoadBitmap(mainWindow.getHInstance(), MAKEINTRESOURCE(IDB_BITMAP1));
	
	
	/*LONG cb = BMP.bmWidth * BMP.bmHeight * (BMP.bmBitsPixel / 8);
	GetBitmapBits(hBMP,	cb,	BMP.bmBits);*/


	return TRUE;
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);

	wglMakeCurrent(0, 0);
	wglDeleteContext(wglGetCurrentContext());
}

void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	mainWindow.moveElements(cx, cy, widthSettings);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	windowPicture.setViewport(ps.rcPaint);

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light_position[] = { 0.0, 1.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glShadeModel(GL_FLAT);

	glRotated(ax, 1, 0, 0);
	glRotated(ay, 0, 1, 0);
	glScaled(m, m, m);

	glLineWidth(1);
	windowPicture.draw();

	GLfloat coordinatesAxes = 7;
	GLfloat coordinatesText = coordinatesAxes + 0.5;
	glColor3f(1, 0.5, 0.1);

	OutText((char*)"X", coordinatesText, 0, 0);
	OutText((char*)"Y", 0, coordinatesText, 0);
	OutText((char*)"Z", 0, 0, coordinatesText);

	SwapBuffers(wglGetCurrentDC());
	EndPaint(hwnd, &ps);
}

int mouseX = 0;

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	mouseX = x;
	if (canMove)
	{
		ax += (y - Y0) / 2.0;
		ay += (x - X0) / 2.0;
		X0 = x;
		Y0 = y;
		InvalidateRect(hwnd, NULL, true);
	}
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	if (x <= rc.right - widthSettings - 10)
	{
		canMove = true;
		X0 = x;
		Y0 = y;
	}
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	canMove = false;
}

void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys)
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	if (mouseX <= rc.right - widthSettings - 10)
	{
		m += (-zDelta / 1000.0);
		if (m < 0.6) m = 0.6;
		if (m > 1.3)   m = 1.3;
		InvalidateRect(hwnd, NULL, true);
	}
}

BOOL OnEraseBkgnd(HWND hwnd, HDC hdc)
{
	return 0;
}

void OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	BOOL error;
	GLdouble stepUD = 0.1;
	GLdouble result = stepUD * pos;
	char buffer[10];
	sprintf(buffer, "%.1f", result);

	if (hwndCtl == mainWindow.getElement("UpDown_A"))
	{
		SendMessage(
			mainWindow.getElement("Edit_A"),
			WM_SETTEXT,
			0,
			(LPARAM)buffer
		);
		equationCoefficients[0] = atof(buffer);		
	}
	else if (hwndCtl == mainWindow.getElement("UpDown_B"))
	{
		SendMessage(
			mainWindow.getElement("Edit_B"),
			WM_SETTEXT,
			0,
			(LPARAM)buffer
		);
		equationCoefficients[1] = atof(buffer);
	}
	else if (hwndCtl == mainWindow.getElement("UpDown_C"))
	{
		SendMessage(
			mainWindow.getElement("Edit_C"),
			WM_SETTEXT,
			0,
			(LPARAM)buffer
		);
		equationCoefficients[2] = atof(buffer);
	}
	else if (hwndCtl == mainWindow.getElement("UpDown_D"))
	{
		SendMessage(
			mainWindow.getElement("Edit_D"),
			WM_SETTEXT,
			0,
			(LPARAM)buffer
		);
		equationCoefficients[3] = atof(buffer);
	}
	windowPicture.setEquationCoefficients(canClip, equationCoefficients);
	InvalidateRect(hwnd, NULL, true);
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case 14:
		SendMessage(mainWindow.getElement("RadioButton_Ortho"), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(mainWindow.getElement("RadioButton_Perspective"), BM_SETCHECK, BST_UNCHECKED, 0);
		windowPicture.setViewMode(MODE_ORTHO);
		InvalidateRect(hwnd, NULL, true);
		break;
	case 15:
		SendMessage(mainWindow.getElement("RadioButton_Perspective"), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(mainWindow.getElement("RadioButton_Ortho"), BM_SETCHECK, BST_UNCHECKED, 0);
		windowPicture.setViewMode(MODE_PERSPECTIVE);
		InvalidateRect(hwnd, NULL, true);
		break;
	case 16:
		SendMessage(mainWindow.getElement("RadioButton_FillMode"), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(mainWindow.getElement("RadioButton_LineMode"), BM_SETCHECK, BST_UNCHECKED, 0);
		windowPicture.setStyle(GLU_FILL);
		InvalidateRect(hwnd, NULL, true);
		break;
	case 17:
		SendMessage(mainWindow.getElement("RadioButton_LineMode"), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(mainWindow.getElement("RadioButton_FillMode"), BM_SETCHECK, BST_UNCHECKED, 0);
		windowPicture.setStyle(GLU_LINE);
		InvalidateRect(hwnd, NULL, true);
		break;

	case 1:
	{
		if (SendMessage(mainWindow.getElement("CheckBox_ClipPlane"), BM_GETCHECK, 0, 0) == BST_UNCHECKED)
		{
			SendMessage(mainWindow.getElement("CheckBox_ClipPlane"), BM_SETCHECK, BST_CHECKED, 0);
			const UINT size = 6;
			TCHAR buffer[size + 1];
			GetDlgItemText(hwnd, 3, buffer, size);
			equationCoefficients[0] = atof(buffer);
			GetDlgItemText(hwnd, 6, buffer, size);
			equationCoefficients[1] = atof(buffer);
			GetDlgItemText(hwnd, 9, buffer, size);
			equationCoefficients[2] = atof(buffer);
			GetDlgItemText(hwnd, 12, buffer, size);
			equationCoefficients[3] = atof(buffer);
		
			canClip = true;
		}
		else
		{
			SendMessage(mainWindow.getElement("CheckBox_ClipPlane"), BM_SETCHECK, BST_UNCHECKED, 0);
			canClip = false;
		}
		windowPicture.setEquationCoefficients(canClip, equationCoefficients);
		InvalidateRect(hwnd, NULL, true);
	}
	break;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);	  
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
		HANDLE_MSG(hWnd, WM_MOUSEWHEEL, OnMouseWheel);
		HANDLE_MSG(hWnd, WM_ERASEBKGND, OnEraseBkgnd);
		HANDLE_MSG(hWnd, WM_VSCROLL, OnVScroll);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}