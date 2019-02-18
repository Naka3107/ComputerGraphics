#include <iostream>

// Siempre que quieran utilizar OpenGL en 
// algun archivo, tienen que incluirlos 
// en este orden.
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "t.h"

float angle = 0.0f;

void render_loop()
{
	t::tick();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glClearColor(sin(t::elapsed_time().count()), 220.0f / 256, 20.0f / 256, 60.0f / 256);

	// WARNING: Esto es OpenGL viejo y solo lo vamos a usar en esta clase.

	//glRotatef(90.0f * t::delta_time().count(), 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);

	glEnd();
	glPopMatrix();
	angle += 1;

	glutSwapBuffers();

	// OpenGL entra en un estado de espera.
}

void idle()
{
	// Cuando OpenGL esta en estado de espera,,
	// vuelve a dibujar
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	// Inicializar Freeglut
	// Freeglut es la libreria para abrir ventanas
	// y configurar el contexto de OpenGL
	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Hello, World!");
	glutDisplayFunc(render_loop);

	glutIdleFunc(idle);

	// Inicializar GLEW
	// GLEW busca el API de OpenGL directamente en la tarjeta de
	// video. Microsoft no lo expone directamente.
	glewInit();

	// Configurar OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	// Mostrar Version de OpenGL
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Ejecutar el ciclo infinito (render loop)
	// Se pausa la ejecucion del main
	glutMainLoop();


	return 0;
}