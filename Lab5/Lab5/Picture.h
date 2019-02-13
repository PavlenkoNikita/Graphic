#pragma once
#define MODE_ORTHO       0
#define MODE_PERSPECTIVE 1

class Picture
{
private:
	GLenum					    viewMode;
	GLint                       width;
	GLint					    height;
	std::vector<QuadricObject*> primitives; 

	void setOrtho();
	void setPerspective();
	void drawAxses();
	void drawGrid();
public:
	Picture();

	void draw();
	void initialization();
	void addTexture(GLuint* p_texturesID);
	void setViewport(RECT p_r);
	void setViewMode(GLenum p_mode);
	void setStyle(GLenum p_style);
	void setPositionPrimitives(std::vector<GLfloat>* p_positions);
	void setEquationCoefficients(
		GLboolean p_isClipPlane,
		std::vector<GLdouble> p_equationCoefficients
	);

	~Picture();
};