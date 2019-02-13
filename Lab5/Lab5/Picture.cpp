#include "stdafx.h"
#include "StdWindow.h"
#include "Picture.h"
#include "resource.h"

Picture::Picture()
{ 
	Sphere* sphere = new Sphere(
		GLU_LINE,
		std::vector<GLfloat>{1, 0, 0},
		2.5
	);

	Cylinder* cylinder = new Cylinder(
		GLU_LINE,
		std::vector<GLfloat>{0, 0, 1},
		2.5,
		2.5,
		2.5
	);

	PartialDisk* partialDisk = new PartialDisk(
		GLU_LINE,
		std::vector<GLfloat>{0, 1, 0},
		1.5,
		3.5,
		315,
		225
	);
	
	primitives.push_back(sphere);
	primitives.push_back(partialDisk);
	primitives.push_back(cylinder);
	
	viewMode = MODE_ORTHO;
}

void Picture::draw()
{
	drawAxses();
	drawGrid();
	for (int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->draw();
	}
}

void Picture::initialization()
{
	for (int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->initializationList();
	}
}

void Picture::addTexture(GLuint* p_texturesID)
{
	for (int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->setTexture(p_texturesID[i]);
	}
}

void Picture::setViewport(RECT pRectangle)
{
	height = pRectangle.bottom - pRectangle.top;
	width = pRectangle.right - pRectangle.left;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width > height)
	{
		glViewport((width - height) / 2, 0, height, height);
	}
	else
	{
		glViewport(0, (height - width) / 2, width, width);
	}

	if (viewMode == MODE_PERSPECTIVE)
	{
		setPerspective();
	}
	else if (viewMode == MODE_ORTHO)
	{
		setOrtho();
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Picture::setViewMode(GLenum mode)
{
	if (viewMode != mode)
	{
		viewMode = mode;
		initialization();
	}
}

void Picture::setStyle(GLenum pstyle)
{
	for (int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->setStyle(pstyle);
	}
}

void Picture::setPositionPrimitives(std::vector<GLfloat>* p_positions)
{
	for (int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->setPosition(p_positions[i]);
	}
}

void Picture::setEquationCoefficients(GLboolean	p_isClipPlane, std::vector<GLdouble> p_equationCoefficients)
{
	primitives[0]->setEquationCoefficients(p_isClipPlane, p_equationCoefficients);
}

void Picture::setOrtho()
{
	glOrtho(-10, 10, -10, 10, -17, 17);
	glRotated(45, 1, 0, 0);
}
	
void Picture::setPerspective()
{
	gluPerspective(100, (GLdouble)width / height, 1, 100);
	gluLookAt(-8.0, -8.0, -8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Picture::drawAxses()
{
	glColor3d(0, 0, 0);
	GLfloat coordinatesAxes = 7;

	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3d(-coordinatesAxes, 0, 0);	glVertex3d(coordinatesAxes, 0, 0);
	glVertex3d(0, -coordinatesAxes, 0);	glVertex3d(0, coordinatesAxes, 0);
	glVertex3d(0, 0, -coordinatesAxes);	glVertex3d(0, 0, coordinatesAxes);
	glEnd();
}

void Picture::drawGrid()
{
	glColor3d(0, 0, 0);
	GLfloat coordinatesAxes = 7;
	glLineWidth(0.5f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x00FF);
	glBegin(GL_LINES);
	double d = coordinatesAxes * 0.1;
	for (
		double i = -coordinatesAxes;
		i <= coordinatesAxes + d;
		i += d
		)
	{
		glVertex3d(i, -coordinatesAxes, 0);	glVertex3d(i, coordinatesAxes, 0);
		glVertex3d(-coordinatesAxes, i, 0);	glVertex3d(coordinatesAxes, i, 0);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

Picture::~Picture()
{
}

//void Picture::initTexture()
//{
//	float color[]{ 1.0, 1.0, 1.0 };
//	glColor3fv(color);
//	HBITMAP hBMP;
//	BITMAP  BMP;
//	GLuint texture;
//	glGenTextures(1, &texture);
//
//	//hBMP = LoadBitmap(mainWindow.getHInstance(), MAKEINTRESOURCE(IDB_BITMAP1));
//	hBMP = (HBITMAP)LoadImage(NULL, "cloth.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//
//	int p = GetObject(hBMP, sizeof(BMP), (LPVOID)&BMP);
//	/*LONG cb = BMP.bmWidth * BMP.bmHeight * (BMP.bmBitsPixel / 8);
//	GetBitmapBits(
//		hBMP,
//		cb,
//		BMP.bmBits
//	);*/
//	
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
//	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
//
//	glEnable(GL_TEXTURE_2D);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
//
//
//	GLUquadricObj *quadObj = gluNewQuadric();
//	gluQuadricTexture(quadObj, GL_TRUE);
//
//	glPushMatrix();
//	glTranslatef(0, 0, 0);
//	gluPartialDisk(quadObj, 1.5, 2.5, 25, 25, 315, 225);
//	//gluSphere(quadObj, 2.5, 25, 25);
//
//	glDeleteTextures(1, &texture);
//
//	glPopMatrix();
//	glDisable(GL_TEXTURE_2D);
//}
