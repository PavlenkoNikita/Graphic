#pragma once
class Scene : public DrawingObject
{
private:
	KinematicScheme kinematicScheme;

	void setPerspective(GLfloat p_width, GLfloat p_height);
	void setOrtho();
	
	void drawWalls();
public:
	Scene();

	void draw() override;
	void setViewPort(RECT p_rectangle);
	void setParamsToScheme(GLfloat p_angleYOZ, GLfloat p_angleAC, GLfloat p_S);
	void bindTexturesToScheme(GLuint* p_texturesID);

	~Scene();
};