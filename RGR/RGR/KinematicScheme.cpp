#include "stdafx.h"
#include "KinematicScheme.h"

#define _USE_MATH_DEFINES
#include <math.h> 


KinematicScheme::KinematicScheme()
{
	sizeA = 0.46, sizeB = 0.82, sizeC = 0.6;
	angleBC = 0, angleOC = 0, angleAC = 25, angleYOZ = 0;
	radiusSegment = 0.035, radiusConnectionSegment = 0.05, lenthConnectionSegment = 0.1;
}

KinematicScheme::KinematicScheme(std::map<UINT, QuadricObject*> p_primitives)
{
	primitives = p_primitives;
	sizeA = 0.46, sizeB = 0.82, sizeC = 0.6;
	angleBC = 0, angleOC = 0, angleAC = 25, angleYOZ = 0;
	radiusSegment = 0.035, radiusConnectionSegment = 0.05, lenthConnectionSegment = 0.1;
}

void KinematicScheme::ComponentAC()
{
	//AC
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glRotatef(angleOC, 0, -1, 0);
		glTranslatef(0, 0, -sizeA);
		glRotatef(-angleAC - angleOC, 0, -1, 0);
		primitives[10]->draw();
		//Point C
		glPushMatrix();
			glRotatef(90, -1, 0, 0);
			//Gag
			glPushMatrix();
				glTranslatef(0, 0, -radiusConnectionSegment);
				primitives[11]->draw();
				glTranslatef(0, 0, radiusConnectionSegment * 2);
				primitives[11]->draw();
			glPopMatrix();
			glTranslatef(0, 0, -radiusConnectionSegment);
			primitives[12]->draw();
			//Point A
			glTranslatef(0, -sizeB, radiusConnectionSegment);
			glRotatef(90, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			primitives[13]->draw();
		glPopMatrix();
	glPopMatrix();
}

void KinematicScheme::ComponentBC()
{
	//BC
	glPushMatrix();
		glRotatef(90, 0, -1, 0);
		glTranslatef(0, S, -sizeC);
		//Slider Verical component
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, -0.12);
			//Gag
			glPushMatrix();
				primitives[5]->draw();
				glTranslatef(0, 0, 0.24);
				primitives[5]->draw();
			glPopMatrix();
			primitives[6]->draw();
		glPopMatrix();
		//Slider Gorizontal component
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, -0.09);
			//Gag
			glPushMatrix();
			primitives[7]->draw();
				glTranslatef(0, 0, 0.18);
				primitives[7]->draw();
			glPopMatrix();
			primitives[8]->draw();
		glPopMatrix();
		glRotatef(angleBC, -1, 0, 0);
		primitives[9]->draw();
	glPopMatrix();
}

void KinematicScheme::ComponentOC()
{
	//point Î
	glPushMatrix();
		//Gag
		glPushMatrix();
			glTranslatef(0, 0, -radiusConnectionSegment);
			primitives[2]->draw();
			glTranslatef(0, 0, radiusConnectionSegment * 2);
			primitives[2]->draw();
		glPopMatrix();
		glTranslatef(0, 0, -radiusConnectionSegment);
		primitives[3]->draw();
	glPopMatrix();
	//OC
	glPushMatrix();
		glRotatef(90, -1, 0, 0);
		glRotatef(angleOC, 0, 1, 0);
		primitives[4]->draw();
	glPopMatrix();
}

void KinematicScheme::ComponentTrajectoryComponent()
{
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
		glColor4f(1, 1, 1, 0.3);
		glTranslatef(sizeC, 0, 0);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, 0, -1);
		primitives[1]->draw();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	glEnable(GL_DEPTH_TEST);
}

void KinematicScheme::draw()
{
	glPushMatrix();
		glRotatef(angleYOZ, 0, 1, 0);
		ComponentTrajectoryComponent();
		ComponentAC();
		ComponentBC();
		ComponentOC();
	glPopMatrix();
}

void KinematicScheme::setSizeLine(GLfloat p_sizeA, GLfloat p_sizeB, GLfloat p_sizeC)
{
	sizeA = p_sizeA; 
	sizeB = p_sizeB;
	sizeC = p_sizeC;
}

void KinematicScheme::setAngles(GLfloat p_angleOC, GLfloat p_angleBC, GLfloat p_angleAC, GLfloat p_angleYOZ)
{
	angleOC  = p_angleOC;
	angleBC  = p_angleBC;
	angleAC  = p_angleAC;
	angleYOZ = p_angleYOZ;
}

void KinematicScheme::setParamsControl(GLfloat p_angleYOZ, GLfloat p_angleAC, GLfloat p_S)
{
	angleYOZ = p_angleYOZ, angleAC = p_angleAC, S = p_S;
	GLfloat c = sqrt(pow(S, 2) + pow(sizeC, 2));
	GLfloat sizeS = fabsf(S);
	if (S <= 0)
	{
		angA = acos((pow(sizeC, 2) + pow(c, 2) - pow(sizeS, 2)) / (2 * sizeC * c)) * 180 / M_PI;
		angB = acos((pow(sizeA, 2) + pow(c, 2) - pow(sizeC, 2)) / (2 * sizeA * c)) * 180 / M_PI;
		angleOC = 90 + angA + angB;

		angC = acos((pow(sizeS, 2) + pow(c, 2) - pow(sizeC, 2)) / (2 * sizeS * c)) * 180 / M_PI;
		angD = acos((pow(sizeC, 2) + pow(c, 2) - pow(sizeA, 2)) / (2 * sizeC * c)) * 180 / M_PI;
		angleBC = 90 - (angC + angD);
	}
	else
	{
		angA = acos((pow(sizeA, 2) + pow(c, 2) - pow(sizeC, 2)) / (2 * sizeA * c)) * 180 / M_PI;
		angB = acos((pow(sizeS, 2) + pow(c, 2) - pow(sizeC, 2)) / (2 * sizeS * c)) * 180 / M_PI;
		angleOC = angA + angB;

		angC = acos((pow(sizeC, 2) + pow(c, 2) - pow(sizeS, 2)) / (2 * sizeC * c)) * 180 / M_PI;
		angD = acos((pow(sizeC, 2) + pow(c, 2) - pow(sizeA, 2)) / (2 * sizeC * c)) * 180 / M_PI;
		angleBC = -(angC + angD);
	}
}

void KinematicScheme::bindTextures(GLuint* p_texturesID)
{
	GLuint i = 0;
	for (std::map<UINT, QuadricObject*>::iterator it = primitives.begin();
		it != primitives.end();
		++i, ++it)
		it->second->setTexture(p_texturesID[i]);
}

KinematicScheme::~KinematicScheme()
{
	primitives.clear();
}