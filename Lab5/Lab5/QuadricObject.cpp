#include "stdafx.h"

QuadricObject::QuadricObject(GLenum p_Style,
	std::vector<GLfloat> p_Color)
	: DrawingObject(p_Style, p_Color)
{
	textureID = 0;
	position = std::vector<GLfloat>(3, 0);
}

void QuadricObject::initializationList()
{
	glDeleteLists(index, 1);
	index = glGenLists(1);
	glNewList(index, GL_COMPILE);
		GLUquadricObj *quadObj = gluNewQuadric();
		if (style == GLU_LINE)
		{
			glColor3fv(color.data());
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color.data());
			gluQuadricDrawStyle(quadObj, style);
		}
		else
		{
			GLfloat temp_color[]{ 1.0, 1.0, 1.0 };

			glColor3fv(temp_color);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, temp_color);
			glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color.data());

			gluQuadricTexture(quadObj, GL_TRUE);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glEnable(GL_TEXTURE_2D);
		}
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new float[4]{ 0, 0, 0, 0 });

		glPushMatrix();
			glTranslatef(position[0], position[1], position[2]);
			initializationQuadricObject(quadObj);
		glPopMatrix();

		if (style == GLU_FILL)
		{
			glDisable(GL_TEXTURE_2D);
		}
		gluDeleteQuadric(quadObj);
	glEndList();
}

void QuadricObject::draw()
{
	glCallList(index);
}

void QuadricObject::setTexture(GLuint p_textureID)
{
	textureID = p_textureID;
}

void QuadricObject::setStyle(GLenum pstyle)
{
	if (style != pstyle)
	{
		style = pstyle;
		initializationList();
	}
}

void QuadricObject::setEquationCoefficients(GLboolean p_isClipPlane, std::vector<GLdouble> p_equationCoefficients)
{
}

QuadricObject::~QuadricObject()
{
	glDeleteLists(index, 1);
}