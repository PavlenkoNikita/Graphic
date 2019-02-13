#include "stdafx.h"

DrawingObject::DrawingObject(GLenum p_style, std::vector<GLfloat> p_color)
{
	style = p_style;
	color = p_color;
}

void DrawingObject::setPosition(std::vector<GLfloat> p_position)
{
	position = p_position;
}

void DrawingObject::setStyle(GLenum p_style)
{
	style = p_style;
}

void DrawingObject::setColor(std::vector<GLfloat> p_color)
{
	color = p_color;
}