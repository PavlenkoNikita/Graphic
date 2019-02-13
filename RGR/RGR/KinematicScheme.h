#pragma once
class KinematicScheme : public DrawingObject
{
private:
	std::map<UINT, QuadricObject*> primitives;

	GLfloat sizeA,
			sizeB,
			sizeC,
			S;
	GLfloat angleBC,
			angleOC, 
			angleAC,
			angleYOZ;
	GLfloat angA,
			angB,
			angC,
			angD;
	GLfloat radiusSegment,
		    radiusConnectionSegment,
		    lenthConnectionSegment;

	static const GLint countTextures = 13;

	void ComponentAC();
	void ComponentBC();
	void ComponentOC();
	void ComponentTrajectoryComponent();
public:
	KinematicScheme();
	KinematicScheme(std::map<UINT, QuadricObject*> p_primitives);

	void draw() override;
	void setSizeLine(GLfloat p_sizeA, GLfloat p_sizeB, GLfloat p_sizeC);
	void setAngles(GLfloat p_angleOC, GLfloat p_angleBC, GLfloat p_angleAC, GLfloat p_angleYOZ);
	void setParamsControl(GLfloat p_angleYOZ, GLfloat p_angleAC, GLfloat p_S);
	void bindTextures(GLuint* p_texturesID);

	~KinematicScheme();
};