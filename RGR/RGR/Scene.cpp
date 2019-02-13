#include "stdafx.h"

Scene::Scene()
{
	GLfloat sizeA = 0.46, sizeB = 0.82, sizeC = 0.6;
	GLfloat radiusSegment = 0.035;
	GLfloat	radiusConnectionSegment = 0.05;
	GLfloat	lenthConnectionSegment = 0.1;

	std::map<UINT, QuadricObject*> primitives;
	primitives.insert(std::pair<UINT, Cylinder*>(1, new Cylinder(0.11, 0.11, 2))); //Trajectory
	primitives.insert(std::pair<UINT, Disk*>(2, new Disk(0, radiusConnectionSegment))); //Gag_O
	primitives.insert(std::pair<UINT, Cylinder*>(3, new Cylinder(radiusConnectionSegment, radiusConnectionSegment, lenthConnectionSegment))); //O
	primitives.insert(std::pair<UINT, Cylinder*>(4, new Cylinder(radiusSegment, radiusSegment, sizeA))); //OC
	primitives.insert(std::pair<UINT, Disk*>(5, new Disk(0, 0.06)));//Gag_VSlider
	primitives.insert(std::pair<UINT, Cylinder*>(6, new Cylinder(0.06, 0.06, 0.24))); //VSlider
	primitives.insert(std::pair<UINT, Disk*>(7, new Disk(0, 0.04))); //Gag_GSlider
	primitives.insert(std::pair<UINT, Cylinder*>(8, new Cylinder(0.04, 0.04, 0.18))); //GSlider
	primitives.insert(std::pair<UINT, Cylinder*>(9, new Cylinder(radiusSegment, radiusSegment, sizeC))); //BC
	primitives.insert(std::pair<UINT, Cylinder*>(10, new Cylinder(radiusSegment, radiusSegment, sizeB))); //AC
	primitives.insert(std::pair<UINT, Disk*>(11, new Disk(0, radiusConnectionSegment))); //Gag_C
	primitives.insert(std::pair<UINT, Cylinder*>(12, new Cylinder(radiusConnectionSegment, radiusConnectionSegment, lenthConnectionSegment)));//C
	primitives.insert(std::pair<UINT, Cylinder*>(13, new Cylinder(radiusSegment, 0.00, 0.1))); //A
	kinematicScheme = KinematicScheme(std::move(primitives));
}

void Scene::draw()
{
	drawWalls();
	kinematicScheme.draw();
}

void Scene::setViewPort(RECT p_rectangle)
{
	GLint height = p_rectangle.bottom - p_rectangle.top;
	GLint width = p_rectangle.right - p_rectangle.left;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*if (width > height)
	{
		glViewport((width - height) / 2, 0, height, height);
	}
	else
	{
		glViewport(0, (height - width) / 2, width, width);
	}
	setOrtho();*/
	glViewport(0, 0, width, height);
	setPerspective(width, height);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Scene::setParamsToScheme(GLfloat p_angleYOZ, GLfloat p_angleAC, GLfloat p_S)
{
	kinematicScheme.setParamsControl(p_angleYOZ, p_angleAC, p_S);
}

void Scene::bindTexturesToScheme(GLuint * p_texturesID)
{
	kinematicScheme.bindTextures(p_texturesID);
}

void Scene::setOrtho()
{
	glOrtho(-1.4, 1.4, -1.4, 1.4, -1.4, 1.4);
}

void Scene::drawWalls()
{
	GLfloat minY = -1.4, maxY = 1.4;
	//Axes
	glLineWidth(0.05);
	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	GLfloat d = maxY * 0.2;
	for (GLfloat i = -maxY;
		i <= 1 + 2 * d;
		i += d)
	{
		//-Z
		glVertex3d(i, -maxY, -maxY);	glVertex3d(i, maxY, -maxY);
		glVertex3d(-maxY, i, -maxY);	glVertex3d(maxY, i, -maxY);
		//-X
		glVertex3d(-maxY, -maxY, i);	glVertex3d(-maxY, maxY, i);
		glVertex3d(-maxY, i, -maxY);    glVertex3d(-maxY, i, maxY);
		//-Y
		glVertex3d(i, -maxY, maxY);	glVertex3d(i, -maxY, -maxY);
		glVertex3d(-maxY, -maxY, i);	glVertex3d(maxY, -maxY, i);
	}
	glEnd();
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex3f(0, minY, 0); glVertex3f(0, maxY, 0);
	glEnd();
}

void Scene::setPerspective(GLfloat p_width, GLfloat p_height)
{
	gluPerspective(100, (GLdouble)p_width / p_height, 0.1, 100);
	gluLookAt(1.3, 0.0, 1.3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

Scene::~Scene()
{
}