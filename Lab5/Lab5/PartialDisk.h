#pragma once

class PartialDisk :
	public QuadricObject
{
private:
	GLushort r;
	GLushort R;
	GLushort startAngle;
	GLushort sweepAngle;
public:
	PartialDisk(
		GLenum pStyle,
		std::vector<GLfloat> pColor,
		std::vector<GLfloat> ppointTranslate,
		GLushort pr,
		GLushort pR,
		GLushort pstartAngle,
		GLushort psweepAngle
	);

	void initializationObject(GLUquadricObj* pObj) override;

	~PartialDisk();
};

