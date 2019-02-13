#pragma once

class Cylinder :
	public QuadricObject
{
private:
	GLdouble R;
	GLdouble r;
	GLdouble h;
public:
	Cylinder(
		GLenum p_Style,
		std::vector<GLfloat> p_Color,
		std::vector<GLfloat> p_pointTranslate,
		GLdouble p_R,
		GLdouble p_r,
		GLdouble p_h
	);

	void initializationObject(GLUquadricObj* pObj) override;

	~Cylinder();
};

