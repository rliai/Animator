// The sample robotarm model.  You should build a file
// very similar to this for when you make your model.
#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning(disable : 4786)

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "particleSystem.h"


#include <FL/gl.h>
#include <stdlib.h>

#include <string>
#include "modelerglobals.h"

#define M_DEFAULT 2.0f
#define M_OFFSET 3.0f
#define P_OFFSET 0.3f
#define MAX_VEL 200
#define MIN_STEP 0.1


class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char *label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{
	return new SampleModel(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
	glScaled(0.7, 0.7, 0.7);

	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glTranslated(0, -5, 0);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();


	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(1, 1, 1);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));


	//body
	glPushMatrix();
	glTranslated(-1.5, 4 + VAL(HEIGHT), -1);
	drawBox(3, 4, 2);

	//left leg
	if (VAL(LEVEL) > 1) {
		glPushMatrix();
		glTranslated(0.25, -3.5 - VAL(HEIGHT), 0.25);
		drawBox(1, 3.5 + VAL(HEIGHT), 1.5);
		glTranslated(0, -0.5, 0);
		drawBox(1, 0.5, 2);
		glPopMatrix();


		//right leg
		glPushMatrix();
		glTranslated(1.75, -3.5 - VAL(HEIGHT), 0.25);
		drawBox(1, 3.5 + VAL(HEIGHT), 1.5);
		glTranslated(0, -0.5, 0);
		drawBox(1, 0.5, 2);
		glPopMatrix();
	}

	//left arm
	if (VAL(LEVEL) > 1) {
		glPushMatrix();

		glTranslated(-1, 3.5, 0);
		drawBox(1, 0.5, 2);
	}

	if (VAL(LEVEL) > 2) {
		// da bi
		glRotated(180, 1, 0, 0);
		glRotated(-VAL(ROTATE), 1, 0, 0);
		drawBox(1, 1.5, -2);
	}

	if (VAL(LEVEL) > 3) {
		// xiao bi
		glEnable(GL_TEXTURE_2D);
		GLuint m_texture = 0;
		glBindTexture(GL_TEXTURE_2D, m_texture);
		drawTexture((string)"texture.jpg", m_texture);

		glTranslated(0.5, 1.5, -1);
		glRotated(-90, 1, 0, 0);
		glRotated(-1.5*VAL(ROTATE), 1, 0, 0);
		drawCylinder(3, 0.5, 0.4);

		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();

	if (VAL(LEVEL) > 1) {
		//right arm
		glPushMatrix();
		glTranslated(3, 3.5, 0);
		drawBox(1, 0.5, 2);
	}
	if (VAL(LEVEL) > 2) {
		// da bi
		glRotated(180, 1, 0, 0);
		glRotated(-VAL(ROTATE), 1, 0, 0);
		drawBox(1, 1.5, -2);
	}

	if (VAL(LEVEL) > 3) {
		// xiaobi
		glEnable(GL_TEXTURE_2D);
		GLuint m_texture = 0;
		glBindTexture(GL_TEXTURE_2D, m_texture);
		drawTexture((string)"texture.jpg", m_texture);

		glTranslated(0.5, 1.5, -1);
		glRotated(-90, 1, 0, 0);
		glRotated(-1.5*VAL(ROTATE), 1, 0, 0);
		drawCylinder(3, 0.5, 0.4);

		glDisable(GL_TEXTURE_2D);

	}
	glPopMatrix();


	//neck
	if (VAL(LEVEL) > 1) {
		glPushMatrix();
		glTranslated(0.75, 4, 0.5);
		drawBox(1.5, 0.5, 1);
	}

	if (VAL(LEVEL) > 2) {
		glTranslated(-0.125, 0.5, 0);
		drawBox(1.75, 1.75, 1);
	}

	if (VAL(LEVEL) > 3) {
		//mouth
		glPushMatrix();
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_RED);
		glTranslated(0.4375, 0.3, 1);
		drawBox(0.875, 0.3, 0.01);
		glPopMatrix();

		//nose
		glPushMatrix();
		glTranslated(0.875, 0.875, 1);

		/*for (int i = 1; i <= 3; i++) {
		drawTriangle(0, 0.5, i/100, 0.25, -0.25, i/100, -0.25, -0.25, i/100);
		}
		*/
		setDiffuseColor(COLOR_GREEN);
		drawTriangle(0, 0, 0.25, 0, 0.25, 0, 0.15, -0.15, 0);
		drawTriangle(0, 0, 0.25, 0, 0.25, 0, -0.15, -0.15, 0);
		drawTriangle(0, 0, 0.25, 0.15, -0.15, 0, -0.15, -0.15, 0);
		//drawTriangle(-0.15, 0.15, 0, 0, 0.25, 0, 0.15, -0.15, 0);
		glPopMatrix();

		//eyes
		glPushMatrix();
		glTranslated(0.58, 1.3, 1);
		drawSphere(0.15);
		glPopMatrix();
		glPushMatrix();
		glTranslated(1.17, 1.3, 1);
		drawSphere(0.15);
		glPopMatrix();

		// tortus or complicated polygons
		glPushMatrix();
		glTranslated(0.875, 2, 0.5);

		if (VAL(INDIVIDUAL) == 0.0f)
		{
			glRotated(90, 1, 0, 0);
			drawTorus(0.05, 0.75);
		}
		else {
			drawTriangle(0, 1, 0, 1, 0, 0, 0.5, 0, -0.86);
			drawTriangle(0, 1, 0, 0.5, 0, -0.86, -0.5, 0, -0.86);
			drawTriangle(0, 1, 0, -0.5, 0, -0.86, -1, 0, 0);
			drawTriangle(0, 1, 0, -1, 0, 0, -0.5, 0, 0.86);
			drawTriangle(0, 1, 0, -0.5, 0, 0.86, 0.5, 0, 0.866);
			drawTriangle(0, 1, 0, 0.5, 0, 0.866, 1, 0, 0);
		}
		glPopMatrix();

	}
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);

	// light controls
	controls[LIGHT0_X] = ModelerControl("Light0 X", -5, 5, 0.1, 4.0);
	controls[LIGHT0_Y] = ModelerControl("Light0 Y", -5, 5, 0.1, 2.0);
	controls[LIGHT0_Z] = ModelerControl("Light0 Z", -5, 5, 0.1, -4.0);
	controls[LIGHT0_R] = ModelerControl("Light0 R", 0.0f, 1.0f, 0.1f, 1.0f);
	controls[LIGHT0_G] = ModelerControl("Light0 G", 0.0f, 1.0f, 0.1f, 1.0f);
	controls[LIGHT0_B] = ModelerControl("Light0 B", 0.0f, 1.0f, 0.1f, 1.0f);

	controls[LIGHT1_X] = ModelerControl("Light1 X", -5.0f, 5.0f, 0.1f, -2.0f);
	controls[LIGHT1_Y] = ModelerControl("Light1 Y", -5.0f, 5.0f, 0.1f, 1.0f);
	controls[LIGHT1_Z] = ModelerControl("Light1 Z", -5.0f, 5.0f, 0.1f, 5.0f);
	controls[LIGHT1_R] = ModelerControl("Light1 R", 0.0f, 1.0f, 0.1f, 1.0f);
	controls[LIGHT1_G] = ModelerControl("Light1 G", 0.0f, 1.0f, 0.1f, 1.0f);
	controls[LIGHT1_B] = ModelerControl("Light1 B", 0.0f, 1.0f, 0.1f, 1.0f);

	controls[LEVEL] = ModelerControl("LEVEL", 1.0f, 4.0f, 1.0f, 4.0f);

	controls[INDIVIDUAL] = ModelerControl("INDIVIDUAL", 0.0f, 1.0f, 1.0f, 0.0f);

	ParticleSystem *ps = new ParticleSystem();
	

	ModelerApplication::Instance()->SetParticleSystem(ps);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
