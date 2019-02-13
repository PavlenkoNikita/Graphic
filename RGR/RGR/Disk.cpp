#include "stdafx.h"
#include "DrawingObject.h"

Disk::Disk()
{
	innerR = 0.5;
	outerR = 1;
}

Disk::Disk(GLfloat p_innerR, GLfloat p_outerR)
	: innerR(p_innerR), outerR(p_outerR)
{
}

void Disk::drawObject()
{
	gluDisk(quadricObject, innerR, outerR, 30, 30);
}

Disk::~Disk()
{
}
