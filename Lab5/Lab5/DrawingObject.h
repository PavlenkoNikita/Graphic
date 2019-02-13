#pragma once
class DrawingObject
{
protected:
	std::vector<GLfloat> color;
	GLenum               style;
	std::vector<GLfloat> position;
public:
	DrawingObject(GLenum p_style, std::vector<GLfloat> p_color);

	void setPosition(std::vector<GLfloat> p_position);
	void setStyle(GLenum p_style);
	void setColor(std::vector<GLfloat> p_color);

	virtual void draw() = 0;
};

class QuadricObject : public DrawingObject
{
protected:
	GLuint               index;
	GLuint               textureID;

	virtual void initializationQuadricObject(GLUquadricObj* p_obj) = 0;
public:
	QuadricObject(
		GLenum               p_style,
		std::vector<GLfloat> p_color
	);

	void setTexture(GLuint p_textureID);
	void setStyle(GLenum p_style);

	virtual void initializationList();
	virtual void draw();
	virtual void setEquationCoefficients(GLboolean p_isClipPlane, std::vector<GLdouble> p_equationCoefficients);

	~QuadricObject();
};

class PartialDisk :
	public QuadricObject
{
private:
	GLushort r;
	GLushort R;
	GLushort startAngle;
	GLushort sweepAngle;

	void initializationQuadricObject(GLUquadricObj* pObj) override;
public:
	PartialDisk(
		GLenum pStyle,
		std::vector<GLfloat> pColor,
		GLushort pr,
		GLushort pR,
		GLushort pstartAngle,
		GLushort psweepAngle
	);	

	~PartialDisk();
};

class Cylinder :
	public QuadricObject
{
private:
	GLdouble R;
	GLdouble r;
	GLdouble h;

	void initializationQuadricObject(GLUquadricObj* pObj) override;
public:
	Cylinder(
		GLenum p_Style,
		std::vector<GLfloat> p_Color,
		GLdouble p_R,
		GLdouble p_r,
		GLdouble p_h
	);

	~Cylinder();
};

class Sphere :
	public QuadricObject
{
private:
	GLfloat               r;
	GLboolean		      isClipPlane;
	std::vector<GLdouble> equationCoefficients;

	void initializationQuadricObject(GLUquadricObj* p_obj) override;
public:
	Sphere(
		GLenum pStyle,
		std::vector<GLfloat> p_color,
		GLfloat pR = 2.5
	);

	void setClipPlane(GLboolean p_isClipPlane);
	void setEquationCoefficients(
		GLboolean p_isClipPlane, 
		std::vector<GLdouble> p_equationCoefficients
	) override;

	~Sphere();
};