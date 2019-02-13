#pragma once

class Sphere :
	public QuadricObject
{
private:
	GLfloat            r;
	GLboolean		   isClipPlane;
	std::vector<GLdouble> equationCoefficients;

public:
	Sphere(
		GLenum pStyle,
		std::vector<GLfloat> p_color,
		std::vector<GLfloat> p_pointTranslate,
		GLfloat pR = 2.5
	);

	void initializationObject(GLUquadricObj* p_obj) override;
	void setClipPlane(GLboolean p_isClipPlane);
	void setEquationCoefficients(
		GLboolean p_isClipPlane
		, std::vector<GLdouble> p_equationCoefficients
	) override;
	
	~Sphere();
};

