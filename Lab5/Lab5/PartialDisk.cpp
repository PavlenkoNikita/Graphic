#include "stdafx.h"

PartialDisk::PartialDisk(
	GLenum p_style,
	std::vector<GLfloat> p_color,
	GLushort p_r,
	GLushort p_R,
	GLushort p_startAngle,
	GLushort p_sweepAngle)
	: QuadricObject(
		p_style,
		p_color
	),
	r(p_r),
	R(p_R),
	startAngle(p_startAngle),
	sweepAngle(p_sweepAngle)
{
}

void PartialDisk::initializationQuadricObject(GLUquadricObj* p_pbj)
{
	glRotatef(90, 1, 0, 0);
	gluPartialDisk(p_pbj, r, R, 25, 25, startAngle, sweepAngle);
}

PartialDisk::~PartialDisk()
{
}
