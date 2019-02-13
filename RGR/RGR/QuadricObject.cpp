#include "stdafx.h"

QuadricObject::QuadricObject()
{
	quadricObject = gluNewQuadric();
	
	gluQuadricDrawStyle(quadricObject, GLU_FILL);
	textureID = 0;
}

void QuadricObject::setTexture(GLuint p_textureID)
{
	textureID = p_textureID;
	gluQuadricTexture(quadricObject, GL_TRUE);
}

void QuadricObject::draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	drawObject();
	glDisable(GL_TEXTURE_2D);
}

QuadricObject::~QuadricObject()
{
	gluDeleteQuadric(quadricObject);
}