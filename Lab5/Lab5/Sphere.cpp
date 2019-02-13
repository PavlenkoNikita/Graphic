#include "stdafx.h"

Sphere::Sphere(
	GLenum pStyle,
	std::vector<GLfloat> p_color,
	GLfloat p_R)
	: QuadricObject(pStyle, p_color), r(p_R) 
{
	isClipPlane = false;
	equationCoefficients = std::vector<GLdouble>(4, 0);
}

void Sphere::initializationQuadricObject(GLUquadricObj* p_obj)
{
	if (isClipPlane)
	{
		glClipPlane(GL_CLIP_PLANE0, equationCoefficients.data());
		glEnable(GL_CLIP_PLANE0);
		gluSphere(p_obj, r, 25, 25);
		glDisable(GL_CLIP_PLANE0);
	}
	else
	{
		gluSphere(p_obj, r, 25, 25);
	}
}

void Sphere::setClipPlane(GLboolean p_isClipPlane)
{
	isClipPlane = p_isClipPlane;
}

void Sphere::setEquationCoefficients(GLboolean p_isClipPlane, std::vector<GLdouble> p_equationCoefficients)
{
	isClipPlane = p_isClipPlane;
	if (isClipPlane)
	{
		for (int i = 0; i < equationCoefficients.size(); i++)
		{
			equationCoefficients[i] = p_equationCoefficients[i];
		}
		initializationList();
	}
	else
	{
		initializationList();
	}
}

Sphere::~Sphere()
{
}
