#include <iostream>
#include <GL/glew.h> // glew apare înainte de freeglut
#include <GL/freeglut.h>

//Se încarcă freeglut.lib
#pragma comment (lib, "freeglut.lib")

void InitGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
	glutInitWindowSize(1000, 700); //dimensiunile ferestrei
}

void Initialize(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f); // culoarea negru de fond a ecranului
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(20.0);
	glBegin(GL_POINTS);
	// X
	for (int index = 0; index < 200000; index++)
	{
		float angle = 360.0f / index * 3.14 * 2;
		float sinus = sin(angle);
		float cosinus = cos(angle);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glVertex4f(sinus, cosinus, 0.0f, 1.0f);

	}
	glEnd();







	glLineWidth(20.0f);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glLineWidth(30.0f);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.7f, -0.7f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.7f, -0.7f, 0.0f);
	glEnd();

	glFlush();


}



int main(int argc, char* argv[])
{
	InitGLUT(argc, argv);
	glutCreateWindow("Primul triunghi - OpenGL <<vechi>>"); // titlul ferestrei
	std::cout << "OpenGL version supported by this platform: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version supported by this platform:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutMainLoop();
	return 0;
}