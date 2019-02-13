#pragma once
class DrawingObject
{
public:
	DrawingObject();

	virtual void draw() = 0;

	~DrawingObject();
};

class QuadricObject : public DrawingObject
{
protected:
	GLint textureID;
	GLUquadric* quadricObject;
	
	virtual void drawObject() = 0;
public:
	QuadricObject();

	virtual void draw();
	void setTexture(GLuint p_textureID);

	~QuadricObject();
};

class Cylinder : public QuadricObject
{
private:
	GLfloat botR;
	GLfloat topR;
	GLfloat	h;

	void drawObject() override;
public:
	Cylinder();
	Cylinder(GLfloat p_botR, GLfloat p_topR, GLfloat p_h);

	~Cylinder();
};

class Disk : public QuadricObject
{
private:
	GLfloat innerR;
	GLfloat outerR;

	void drawObject() override;
public:
	Disk();
	Disk(GLfloat p_innerR, GLfloat p_outerR);

	~Disk();
};