#include "common.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "Cube with Indices";
const double FRAME_RATE_MS = 1000.0 / 60.0;

GLuint Projection;
GLuint vPosition;
GLuint vColor;

glm::vec4 matForU;
glm::vec4 matForV;
glm::vec4 matForVT;
glm::mat4 matForMb;
glm::mat4 matForMbT;
glm::mat4 matForGb;

std::vector<glm::vec4> cps;
std::vector<glm::vec4> points;
std::vector<glm::vec4> colorForCps;
std::vector<int> indices;

float eyeX = 1.0f;
float eyeZ = -1.0f;
int direction = 0;

float increment = 0.1;

int numOfVerticesEachPatch = ((1 / increment) + 1) * ((1 / increment) + 1);
int numOfVerticesEachLine = (1 / increment) + 1;

int patches;
int verticies;

int amout = 0;

void B_patch(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o, int p)
{
	matForMb[0] = glm::vec4( 1, -3,  3, -1 );
	matForMb[1] = glm::vec4( 0,  3, -6,  3 );
	matForMb[2] = glm::vec4( 0,  0,  3, -3 );
	matForMb[3] = glm::vec4( 0,  0,  0,  1 );

	matForMbT[0] = glm::vec4( 1,  0,  0, 0);
	matForMbT[1] = glm::vec4(-3,  3,  0, 0);
	matForMbT[2] = glm::vec4( 3, -6,  3, 0);
	matForMbT[3] = glm::vec4(-1,  3, -3, 1);

	// x
	matForGb[0][0] = cps.at(a - 1).x;
	matForGb[0][1] = cps.at(b - 1).x;
	matForGb[0][2] = cps.at(c - 1).x;
	matForGb[0][3] = cps.at(d - 1).x;
	matForGb[1][0] = cps.at(e - 1).x;
	matForGb[1][1] = cps.at(f - 1).x;
	matForGb[1][2] = cps.at(g - 1).x;
	matForGb[1][3] = cps.at(h - 1).x;
	matForGb[2][0] = cps.at(i - 1).x;
	matForGb[2][1] = cps.at(j - 1).x;
	matForGb[2][2] = cps.at(k - 1).x;
	matForGb[2][3] = cps.at(l - 1).x;
	matForGb[3][0] = cps.at(m - 1).x;
	matForGb[3][1] = cps.at(n - 1).x;
	matForGb[3][2] = cps.at(o - 1).x;
	matForGb[3][3] = cps.at(p - 1).x;
	amout = 0;
	int sizeBeforeNewPoints = points.size();

	for ( double u = 0.0f; u < 1.01f; u += increment )
	{
		amout++;
		for ( double v = 0.0f; v < 1.01f; v += increment )
		{
			matForU = glm::vec4( 1, pow(u, 1), pow(u, 2), pow(u, 3) );
			matForV = glm::vec4( 1, pow(v, 1), pow(v, 2), pow(v, 3) );

			float x = glm::dot(matForU, matForMb * matForGb * matForMbT * matForV);

			glm::vec4 newPoint (x, 0, 0, 1); 

			points.push_back(newPoint);
		}
	}

	int sizeAfterNewPoints = points.size();

	// y
	matForGb[0][0] = cps.at(a - 1).y;
	matForGb[0][1] = cps.at(b - 1).y;
	matForGb[0][2] = cps.at(c - 1).y;
	matForGb[0][3] = cps.at(d - 1).y;
	matForGb[1][0] = cps.at(e - 1).y;
	matForGb[1][1] = cps.at(f - 1).y;
	matForGb[1][2] = cps.at(g - 1).y;
	matForGb[1][3] = cps.at(h - 1).y;
	matForGb[2][0] = cps.at(i - 1).y;
	matForGb[2][1] = cps.at(j - 1).y;
	matForGb[2][2] = cps.at(k - 1).y;
	matForGb[2][3] = cps.at(l - 1).y;
	matForGb[3][0] = cps.at(m - 1).y;
	matForGb[3][1] = cps.at(n - 1).y;
	matForGb[3][2] = cps.at(o - 1).y;
	matForGb[3][3] = cps.at(p - 1).y;

	int copyOfSizeBeforeNewPoints = sizeBeforeNewPoints;

	for (float u = 0; u < 1.01f; u += increment)
	{
		for (float v = 0; v < 1.01f; v += increment)
		{
			matForU = glm::vec4(1, pow(u, 1), pow(u, 2), pow(u, 3));
			matForV = glm::vec4(1, pow(v, 1), pow(v, 2), pow(v, 3));

			float y = glm::dot(matForU, matForMb * matForGb * matForMbT * matForV);

			points.at(sizeBeforeNewPoints).y = y;
			sizeBeforeNewPoints++;
		}
	}

	// z
	matForGb[0][0] = cps.at(a - 1).z;
	matForGb[0][1] = cps.at(b - 1).z;
	matForGb[0][2] = cps.at(c - 1).z;
	matForGb[0][3] = cps.at(d - 1).z;
	matForGb[1][0] = cps.at(e - 1).z;
	matForGb[1][1] = cps.at(f - 1).z;
	matForGb[1][2] = cps.at(g - 1).z;
	matForGb[1][3] = cps.at(h - 1).z;
	matForGb[2][0] = cps.at(i - 1).z;
	matForGb[2][1] = cps.at(j - 1).z;
	matForGb[2][2] = cps.at(k - 1).z;
	matForGb[2][3] = cps.at(l - 1).z;
	matForGb[3][0] = cps.at(m - 1).z;
	matForGb[3][1] = cps.at(n - 1).z;
	matForGb[3][2] = cps.at(o - 1).z;
	matForGb[3][3] = cps.at(p - 1).z;

	sizeBeforeNewPoints = copyOfSizeBeforeNewPoints;
	for (float u = 0; u < 1.01f; u += increment)
	{
		for (float v = 0; v < 1.01f; v += increment)
		{
			matForU = glm::vec4(1, pow(u, 1), pow(u, 2), pow(u, 3));
			matForV = glm::vec4(1, pow(v, 1), pow(v, 2), pow(v, 3));

			float z = glm::dot(matForU, matForMb * matForGb * matForMbT * matForV);
			points.at(sizeBeforeNewPoints).z = z;
			sizeBeforeNewPoints++;
		}
	}
};

void B_point(float x, float y, float z)
{
	glm::vec4 newPoint(x, y, z, 1);
	cps.push_back(newPoint);
};

void Load_patch()
{
	float x, y, z;
	int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	char * filename = "teacup.txt";

	FILE *fp;

	if (!(fp = fopen(filename,"r"))) 
	{
		fprintf(stderr,"Load_patch: Can't open %s\n",filename);
		exit(1);
	}

	fscanf(fp, "%i\n", &verticies);

	for (int ii = 0; ii < verticies; ii++)
	{
		fscanf(fp, "%f, %f, %f\n", &x, &y, &z);
		B_point(x, y, z);
	}

	fscanf(fp,"%i\n", &patches);

	for (int ii = 0; ii < patches; ii++) 
	{
		fscanf(fp,"%i, %i, %i, %i,",&a,&b,&c,&d);
		fscanf(fp,"%i, %i, %i, %i,",&e,&f,&g,&h);
		fscanf(fp,"%i, %i, %i, %i,",&i,&j,&k,&l);
		fscanf(fp,"%i, %i, %i, %i\n",&m,&n,&o,&p);
		B_patch(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
	}
}

void init()
{
	Load_patch();

	for (int i = 0; i < points.size(); i++)
	{
		colorForCps.push_back(glm::vec4(1, 1, 1, 0));
	}

	for (int i = 0; i < cps.size(); i++) 
	{
		colorForCps.push_back( glm::vec4( 1, 0, 0, 0 ) );
	}

	for ( int i = 0; i < patches; i++ )
	{
		for (int j = i * numOfVerticesEachPatch; j < i * numOfVerticesEachPatch + numOfVerticesEachLine; j++)
		{
			for (int q = 0; q < numOfVerticesEachLine * numOfVerticesEachLine; q += numOfVerticesEachLine)
			{
				indices.push_back(j + q);
			}
		}
	}

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * points.size() + sizeof(glm::vec4) * cps.size() + sizeof(glm::vec4) * colorForCps.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * points.size(), &(points.at(0)));
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * points.size(), sizeof(glm::vec4) * cps.size(), &(cps.at(0)));
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * points.size() + sizeof(glm::vec4) * cps.size(), sizeof(glm::vec4) * colorForCps.size(), &(colorForCps.at(0)));

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices.at(0), GL_STATIC_DRAW);

	GLuint program = InitShader("vshader6.glsl", "fshader5.glsl");
	glUseProgram(program);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4) * points.size() + sizeof(glm::vec4) * cps.size()));

	Projection = glGetUniformLocation(program, "Projection");

	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 MV = glm::translate(glm::mat4(), glm::vec3(0, 0, -2)) * glm::scale(glm::mat4(), glm::vec3(0.5, 0.5, 0.5));
	glm::mat4 lookat = glm::lookAt(glm::vec3(eyeX, 1.0f, eyeZ), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 perspective = glm::perspective( glm::radians(45.0f), 1.0f, 1.0f, 3.0f );
	glm::mat4 projection = perspective * lookat * MV;
	glUniformMatrix4fv(Projection, 1, GL_FALSE, glm::value_ptr(projection));

	// draw curve 
	for (int i = 0; i < patches; i++)
	{
		for ( int j = i * numOfVerticesEachPatch; j < ( i + 1 ) * numOfVerticesEachPatch; j += numOfVerticesEachLine )
		{
			glDrawArrays(GL_LINE_STRIP, j, numOfVerticesEachLine);
		}
	}

	for (int i = 0; i < indices.size(); i += numOfVerticesEachLine)
	{
		glDrawElements(GL_LINE_STRIP, numOfVerticesEachLine, GL_UNSIGNED_INT, (void *)(i * numOfVerticesEachLine * sizeof(GLuint)));
	}

	// draw cps 
	glPointSize(3);
	glDrawArrays(GL_POINTS, points.size(), cps.size());

	if (direction == 0)
	{
		eyeX += 0.02;

		if (eyeX > 1)
		{
			eyeX = 1;
			direction = -1;
		}
	}
	else if (direction == 1)
	{
		eyeZ -= 0.02;

		if (eyeZ < -3)
		{
			eyeZ = -3;
			direction = -1;
		}
	}
	else if (direction == 2)
	{
		eyeX -= 0.02;

		if (eyeX < -1)
		{
			eyeX = -1;
			direction = -1;
		}
	}
	else if (direction == 3)
	{
		eyeZ += 0.02;

		if (eyeZ > -1)
		{
			eyeZ = -1;
			direction = -1;
		}
	}

	glutSwapBuffers();
}

void update(void)
{

}

void
reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y)
{
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
		{
			if (direction == -1)
			{
				if (eyeX == 1.0f && eyeZ == -1.0f)
				{
					direction = 1;
				}
				else if (eyeX == 1.0f && eyeZ == -3.0f)
				{
					direction = 2;
				}
				else if (eyeX == -1.0f && eyeZ == -3.0f)
				{
					direction = 3;
				}
				else if (eyeX == -1.0f && eyeZ == -1.0f)
				{
					direction = 0;
				}
			}
		}
		}
	}
}

void drag(int x, int y)
{
}