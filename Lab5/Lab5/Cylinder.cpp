#include "stdafx.h"

Cylinder::Cylinder(GLenum pStyle,
	std::vector<GLfloat> pColor,
	GLdouble pR, GLdouble pr, GLdouble ph)
	: QuadricObject(pStyle, pColor), R(pR), r(pr), h(ph)
{
}

void Cylinder::initializationQuadricObject(GLUquadricObj* pObj)
{
	gluCylinder(pObj, R, r, h, 25, 25);
}

Cylinder::~Cylinder()
{
}