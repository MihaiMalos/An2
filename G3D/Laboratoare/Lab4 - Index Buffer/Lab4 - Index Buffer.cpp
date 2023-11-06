#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h> 
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


// include the freeglut Library file
#pragma comment (lib, "freeglut.lib")
#pragma comment (lib, "glew32.lib")

bool solid = true;
bool bOrthoProj = false;
float fieldOfView = 45.0f;

GLuint VaoId, VboId, IboId, ColorBufferId, VertexShaderId, FragmentShaderId, ProgramId;
GLuint WorldMatrixLocation, ProjMatrixLocation;

glm::mat4 projTransf;
const glm::mat4 GetProjectionMatrix(bool bOrthoProj)
{
	glm::mat4 Proj = glm::mat4(1);
	float width = (float)glutGet(GLUT_WINDOW_WIDTH);
	float height = (float)glutGet(GLUT_WINDOW_HEIGHT);
	float zNear = 0.1f;
	float zFar = 500.f;
	if (bOrthoProj) {
		float scaleFactor = 2000.f;
		Proj = glm::ortho<float>(
			-width / scaleFactor, width / scaleFactor,
			-height / scaleFactor, height / scaleFactor, -zFar, zFar);
	}
	else {
		float aspectRatio = width / height;
		Proj = glm::perspective(glm::radians(fieldOfView), aspectRatio, zNear, zFar);
	}
	return Proj;
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(4, TimerFunction, 1); // 16 milliseconds = ~60 frames per second
}

// Shader-ul de varfuri / Vertex shader (este privit ca un sir de caractere)
const GLchar* VertexShader =
{
	"#version 400\n"\
	"layout(location=0) in vec4 in_Position;\n"\
	"layout(location=1) in vec4 in_Color;\n"\
	"out vec4 ex_Color;\n"\
	"uniform mat4 WorldMatrix;\n"\
	"uniform mat4 ProjMatrix;\n"\
	"void main()\n"\
	"{\n"\
	"  gl_Position = ProjMatrix * WorldMatrix * in_Position;\n"\
	"  ex_Color = in_Color;\n"\
	"}\n"
};
// Shader-ul de fragment / Fragment shader (este privit ca un sir de caractere)
const GLchar* FragmentShader =
{
	"#version 400\n"\
	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\
	"void main()\n"\
	"{\n"\
	"  out_Color = ex_Color;\n"\
	"}\n"
};
void CreateVBO()
{
	// indexurile piramidei
	unsigned int Indices[] = {
		0,1,3,
		1,2,3,
		2,0,3,
		0,1,2
	};

	// varfurile piramidei
	GLfloat Vertices[] = {
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0,
	 1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	// back
	-1.0, -1.0, -1.0,
	 1.0, -1.0, -1.0,
	 1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0
	};
	// culorile, ca atribute ale varfurilor
	GLfloat Colors[] = {
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0
	};

	GLuint indices[] = {
		// Front face
		0, 1, 2,
		2, 3, 0,
		// Back face
		4, 5, 6,
		6, 7, 4,
		// Left face
		0, 3, 7,
		7, 4, 0,
		// Right face
		1, 5, 6,
		6, 2, 1,
		// Top face
		3, 2, 6,
		6, 7, 3,
		// Bottom face
		0, 1, 5,
		5, 4, 0
	};


	// se creeaza un buffer nou
	glGenBuffers(1, &VboId);
	// este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// punctele sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	// 
	glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, 0, 0);

	// un nou buffer, pentru culoare
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	// atributul 1 =  culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 8, GL_FLOAT, GL_FALSE, 0, 0);

	// un nou buffer pentru indexuri
	glGenBuffers(1, &IboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void DestroyVBO()
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
void CreateShaders()
{
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glGetProgramiv(ProgramId, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ProgramId, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(ProgramId);
	glGetProgramiv(ProgramId, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ProgramId, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glUseProgram(ProgramId);

	WorldMatrixLocation = glGetUniformLocation(ProgramId, "WorldMatrix");
	ProjMatrixLocation = glGetUniformLocation(ProgramId, "ProjMatrix");
}
void DestroyShaders()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);
}
void Initialize()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // culoarea de fond a ecranului
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	CreateVBO();
	CreateShaders();
	projTransf = GetProjectionMatrix(bOrthoProj);
}
void RenderFunction()
{
	static float triangleOffset = 0.0f;
	const float triangleIncrement = 0.001f;

	triangleOffset += triangleIncrement;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (solid)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_DEPTH_TEST);
	}

	glm::mat4 worldTransf = glm::translate(glm::mat4(1.0), glm::vec3(0.f, 0.0f, -1.f));
	worldTransf = glm::scale(worldTransf, glm::vec3(0.1f, 0.1f, 0.1f));
	worldTransf = glm::rotate(worldTransf, glm::radians(triangleOffset * 180), glm::vec3(0, 1, 0));

	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldTransf));
	glUniformMatrix4fv(ProjMatrixLocation, 1, GL_FALSE, glm::value_ptr(projTransf));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IboId);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}
static void Keyboard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'w':
		solid = false;
		break;
	case 's':
		solid = true;
		break;
	case 'o':
		bOrthoProj = true;
		projTransf = GetProjectionMatrix(bOrthoProj);
		break;
	case 'p':
		bOrthoProj = false;
		projTransf = GetProjectionMatrix(bOrthoProj);
		break;
	case 'i':
		fieldOfView += 5.0f;
		projTransf = GetProjectionMatrix(bOrthoProj);
		break;
	case 'd':
		fieldOfView -= 5.0f;
		projTransf = GetProjectionMatrix(bOrthoProj);
		break;


	}
}
void Cleanup()
{
	DestroyShaders();
	DestroyVBO();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
	glutInitWindowSize(1000, 700); //dimensiunile ferestrei
	glutCreateWindow("Primul triunghi - OpenGL <<nou>>"); // titlul ferestrei
	// nu uitati de initializare glew; 
	// trebuie initializat inainte de a a initializa desenarea
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutTimerFunc(16, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);

	glutCloseFunc(Cleanup);
	glutMainLoop();
}