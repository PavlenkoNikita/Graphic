#include "stdafx.h"

Cylinder::Cylinder()
{
	h = 1;
	botR = 1;
	topR = 1;
}

Cylinder::Cylinder(GLfloat p_botR, GLfloat p_topR, GLfloat p_h)
	: h(p_h), botR(p_botR), topR(p_topR)
{
}

void Cylinder::drawObject()
{
	gluCylinder(quadricObject, botR, topR, h, 30, 30);
}

Cylinder::~Cylinder()
{
}