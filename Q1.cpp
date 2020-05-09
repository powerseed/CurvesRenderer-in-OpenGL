#include "common.h"
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "Cube with Indices";
const double FRAME_RATE_MS = 1000.0 / 60.0;

GLuint Projection;
GLuint vPosition;

GLuint mode = 1;
int indexOfCPClicked = -1;

glm::mat4 matForCP;
glm::vec4 matForT;

const GLuint Bezier = 1;
glm::mat4 matForBezier;

const GLuint CatmullRom = 2;
glm::mat4 firstMatForCatmullRom;
glm::mat4 secondMatForCatmullRom;

const GLuint BSplines = 3;
glm::mat4 matForBSpline;

std::vector<glm::vec4> cps;
std::vector<glm::vec4> points;

void drawABezierSegment(glm::vec4 p0, glm::vec4 p1, glm::vec4 p2, glm::vec4 p3)
{
	GLfloat t = 0.0f;

	matForCP[0][0] = p0.x;
	matForCP[0][1] = p1.x;
	matForCP[0][2] = p2.x;
	matForCP[0][3] = p3.x;

	matForCP[1][0] = p0.y;
	matForCP[1][1] = p1.y;
	matForCP[1][2] = p2.y;
	matForCP[1][3] = p3.y;

	matForCP[2][0] = p0.z;
	matForCP[2][1] = p1.z;
	matForCP[2][2] = p2.z;
	matForCP[2][3] = p3.z;

	matForCP[3][0] = p0.w;
	matForCP[3][1] = p1.w;
	matForCP[3][2] = p2.w;
	matForCP[3][3] = p3.w;

	while (t <= 1)
	{
		matForT = glm::vec4(pow(t, 3), pow(t, 2), t, 1.0f);
		glm::vec4 newPoint = matForT * matForBezier * matForCP;
		points.push_back(newPoint);
		t += 0.01;
	}
}

void drawACatmullRomSegment( glm::vec4 QkMinusOne, glm::vec4 Qk, glm::vec4 QkPlusOne, glm::vec4 QkPlusTwo )
{
	GLfloat t = 0.0f;

	matForCP[0][0] = QkMinusOne.x;
	matForCP[0][1] = Qk.x;
	matForCP[0][2] = QkPlusOne.x;
	matForCP[0][3] = QkPlusTwo.x;

	matForCP[1][0] = QkMinusOne.y;
	matForCP[1][1] = Qk.y;
	matForCP[1][2] = QkPlusOne.y;
	matForCP[1][3] = QkPlusTwo.y;

	matForCP[2][0] = QkMinusOne.z;
	matForCP[2][1] = Qk.z;
	matForCP[2][2] = QkPlusOne.z;
	matForCP[2][3] = QkPlusTwo.z;

	matForCP[3][0] = QkMinusOne.w;
	matForCP[3][1] = Qk.w;
	matForCP[3][2] = QkPlusOne.w;
	matForCP[3][3] = QkPlusTwo.w;

	while (t <= 1)
	{
		matForT = glm::vec4(pow(t, 3), pow(t, 2), t, 1.0f);
		glm::vec4 newPoint = matForT * firstMatForCatmullRom * secondMatForCatmullRom * matForCP;
		points.push_back(newPoint);
		t += 0.01;
	}
}

void drawABSplineSegment(glm::vec4 QkMinusOne, glm::vec4 Qk, glm::vec4 QkPlusOne, glm::vec4 QkPlusTwo)
{
	GLfloat t = 0.0f;

	matForCP[0][0] = QkMinusOne.x;
	matForCP[0][1] = Qk.x;
	matForCP[0][2] = QkPlusOne.x;
	matForCP[0][3] = QkPlusTwo.x;

	matForCP[1][0] = QkMinusOne.y;
	matForCP[1][1] = Qk.y;
	matForCP[1][2] = QkPlusOne.y;
	matForCP[1][3] = QkPlusTwo.y;

	matForCP[2][0] = QkMinusOne.z;
	matForCP[2][1] = Qk.z;
	matForCP[2][2] = QkPlusOne.z;
	matForCP[2][3] = QkPlusTwo.z;

	matForCP[3][0] = QkMinusOne.w;
	matForCP[3][1] = Qk.w;
	matForCP[3][2] = QkPlusOne.w;
	matForCP[3][3] = QkPlusTwo.w;

	while (t <= 1)
	{
		matForT = glm::vec4(pow(t, 3), pow(t, 2), t, 1.0f);
		glm::vec4 newPoint = matForT * (1.0f / 6.0f) * matForBSpline * matForCP;
		points.push_back(newPoint);
		t += 0.01;
	}
}

void checkIfClickedOnAPoint(int clickedX, int clickedY)
{
	indexOfCPClicked = -1;

	float clickedXInWorldCoordinate = (clickedX - 320) / 320.0f;
	float clickedYInWorldCoordinate = (320 - clickedY) / 320.0f;

	for ( int i = 0; i < cps.size(); i++ )
	{
		if ( distance( glm::vec2(clickedXInWorldCoordinate, clickedYInWorldCoordinate), glm::vec2( cps.at(i).x, cps.at(i).y ) ) <= 0.025f )
		{
			indexOfCPClicked = i;
		}
	}

	//return indexOfCPClicked;
}

void init()
{
	cps.push_back(glm::vec4(-0.5, -0.3, 1, 1));
	cps.push_back(glm::vec4(-0.25, 0.3, 1, 1));
	cps.push_back(glm::vec4(0.25, 0.3, 1, 1));
	cps.push_back(glm::vec4(0.5, -0.3, 1, 1));

	matForBezier[0] = glm::vec4(-1, 3, -3, 1);
	matForBezier[1] = glm::vec4(3, -6, 3, 0);
	matForBezier[2] = glm::vec4(-3, 3, 0, 0);
	matForBezier[3] = glm::vec4(1, 0, 0, 0);

	firstMatForCatmullRom[0] = glm::vec4( 2, -3, 0, 1);
	firstMatForCatmullRom[1] = glm::vec4(-2,  3, 0, 0);
	firstMatForCatmullRom[2] = glm::vec4( 1, -2, 1, 0);
	firstMatForCatmullRom[3] = glm::vec4( 1, -1, 0, 0);

	secondMatForCatmullRom[0] = glm::vec4(0, 0, -0.5f,     0);
	secondMatForCatmullRom[1] = glm::vec4(1, 0,     0, -0.5f);
	secondMatForCatmullRom[2] = glm::vec4(0, 1,   0.5,     0);
	secondMatForCatmullRom[3] = glm::vec4(0, 0,     0,   0.5);

	matForBSpline[0] = glm::vec4(-1,  3, -3, 1);
	matForBSpline[1] = glm::vec4( 3, -6,  0, 4);
	matForBSpline[2] = glm::vec4(-3,  3,  3, 1);
	matForBSpline[3] = glm::vec4( 1,  0,  0, 0);
	
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	GLuint program = InitShader("vshader6Q1.glsl", "fshader5Q1.glsl");
	glUseProgram(program);

	vPosition = glGetAttribLocation(program, "vPosition"); 
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	Projection = glGetUniformLocation(program, "Projection");

	glEnable(GL_DEPTH_TEST);
	std::cout << "Mode: Bezier. " << std::endl;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (mode == Bezier)
	{
		points.clear();
		for (int i = 0; i < cps.size() - 3; i += 3)
		{
			drawABezierSegment(cps.at(i), cps.at(i+1), cps.at(i+2), cps.at(i+3));
		}
	}
	else if (mode == CatmullRom)
	{
		points.clear();
		drawACatmullRomSegment(cps.at(0), cps.at(0), cps.at(1), cps.at(2));

		for (int i = 0; i < cps.size() - 3; i += 1)
		{
			drawACatmullRomSegment( cps.at(i), cps.at(i + 1), cps.at(i + 2), cps.at(i + 3) );
		}

		drawACatmullRomSegment(cps.at(cps.size() - 3), cps.at(cps.size() - 2), cps.at(cps.size() - 1), cps.at(cps.size()-1));
	}
	else if (mode == BSplines)
	{
		points.clear();

		drawABSplineSegment(cps.at(0), cps.at(0), cps.at(1), cps.at(2));

		for (int i = 0; i < cps.size() - 3; i += 1)
		{
			drawABSplineSegment( cps.at(i), cps.at(i + 1), cps.at(i + 2), cps.at(i + 3) );
		}

		drawABSplineSegment(cps.at(cps.size() - 3), cps.at(cps.size() - 2), cps.at(cps.size() - 1), cps.at(cps.size() - 1));
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * points.size() + sizeof(glm::vec4) * cps.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * points.size(), &(points.at(0)));
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * points.size(), sizeof(glm::vec4) * cps.size(), &(cps.at(0)));

	// draw curve 
	glDrawArrays(GL_LINE_STRIP, 0, points.size());

	// draw cps 
	glPointSize(10);
	glDrawArrays(GL_POINTS, points.size(), cps.size());

	glutSwapBuffers();
}

void update(void)
{

}

void
reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(Projection, 1, GL_FALSE, glm::value_ptr(projection));
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
		case ' ': 
			mode++;
			if (mode > 3)
			{
				mode = 1;
			}
			if (mode == Bezier)
			{
				std::cout << "Mode: Bezier. " << std::endl;
			}
			else if (mode == CatmullRom)
			{
				std::cout << "Mode: Catmull-Rom. " << std::endl;
			}
			else if (mode == BSplines)
			{
				std::cout << "Mode: B-Splines. " << std::endl;
			}
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) 
	{
		switch (button) 
		{
			case GLUT_LEFT_BUTTON:
				checkIfClickedOnAPoint(x, y);

				if (indexOfCPClicked == -1)
				{
					float clickedXInWorldCoordinate = (x - 320) / 320.0f;
					float clickedYInWorldCoordinate = (320 - y) / 320.0f;
					cps.push_back(glm::vec4(clickedXInWorldCoordinate, clickedYInWorldCoordinate, 1, 1));
				}
				break;
		}
	}
}

void drag(int x, int y)
{
	if (indexOfCPClicked != -1)
	{
		float clickedXInWorldCoordinate = (x - 320) / 320.0f;
		float clickedYInWorldCoordinate = (320 - y) / 320.0f;

		cps.at(indexOfCPClicked).x = clickedXInWorldCoordinate;
		cps.at(indexOfCPClicked).y = clickedYInWorldCoordinate;
	}
}