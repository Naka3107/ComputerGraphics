#include "scene_manager.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/il.h>

#include "scene.h"
#include "scene_compatibility.h"
#include "scene_primitives.h"
#include "scene_chaikin.h"
#include "scene_conchoid.h"
#include "scene_vertex.h"
#include "scene_circle_grid.h"
#include "scene_sphere.h" 
#include "scene_circle.h" 
#include "scene_cube.h"
#include "scene_texture.h"
#include "scene_shading.h"
#include "scene_rain.h"
#include "t.h"

std::vector<std::unique_ptr<scene>> scene_manager::sceneList;
int scene_manager::currentScene = -1;

void scene_manager::start(int argc, char* argv[], const std::string& name, int width, int height)
{
	// Time init
	t::init();

	// Freeglut init
	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(name.c_str());
	glutDisplayFunc(mainLoop);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutCloseFunc(cleanup);
	glutKeyboardFunc(normalKeysDown);
	glutKeyboardUpFunc(normalKeysUp);
	glutSpecialFunc(specialKeys);
	glutPassiveMotionFunc(passiveMotion);

	// Glew init
	glewInit();

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// GL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Scene init
	initialize();

	// Inicializar DevIL. Esto se debe hacer sólo una vez en
	// todo el ciclo de vida del programa.
	ilInit();
	// Cambiar el punto de origen de las texturas. Por default, DevIL
	// pone un punto de origen en la esquina superior izquierda.
	// Eso es compatible con el sistema operativo, pero no con el
	// funcionamiento de OpenGL.
	ilEnable(IL_ORIGIN_SET);
	// Configurar el punto de origen de las texturas en la esquina
	// inferior izquierda
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	// Run main loop
	glutMainLoop();
}

void scene_manager::next()
{
	int nScenes = (int)sceneList.size();
	if (nScenes > 0)
	{
		sceneList.at(currentScene)->sleep();
		currentScene = (currentScene + 1) % nScenes;
		sceneList.at(currentScene)->awake();
	}
}

void scene_manager::prev()
{
	int nScenes = (int)sceneList.size();
	if (nScenes > 0)
	{
		sceneList.at(currentScene)->sleep();
		currentScene--;
		if (currentScene < 0)
			currentScene = (nScenes - 1);
		sceneList.at(currentScene)->awake();
	}
}

void scene_manager::initialize()
{
	// Ejemplo de como agregar escenas al proyecto
	//std::unique_ptr<scene> somescene(new scene_project);
	//sceneList.push_back(std::move(somescene));
	std::unique_ptr<scene> scene1(new scene_compatibility);
	sceneList.push_back(std::move(scene1));

	std::unique_ptr<scene> scene2(new scene_primitives);
	sceneList.push_back(std::move(scene2));

	std::unique_ptr<scene> scene3(new scene_conchoid);
	sceneList.push_back(std::move(scene3));

	std::unique_ptr<scene> scene4(new scene_chaikin);
	sceneList.push_back(std::move(scene4));

	std::unique_ptr<scene> scene5(new scene_vertex);
	sceneList.push_back(std::move(scene5));

	std::unique_ptr<scene> scene6(new scene_circle_grid);
	sceneList.push_back(std::move(scene6));

	std::unique_ptr<scene> scene7(new scene_sphere);
	sceneList.push_back(std::move(scene7));

	std::unique_ptr<scene> scene8(new scene_circle);
	sceneList.push_back(std::move(scene8));

	std::unique_ptr<scene> scene9(new scene_cube);
	sceneList.push_back(std::move(scene9));

	std::unique_ptr<scene> scene10(new scene_texture);
	sceneList.push_back(std::move(scene10));

	std::unique_ptr<scene> scene11(new scene_shading);
	sceneList.push_back(std::move(scene11));

	std::unique_ptr<scene> scene12(new scene_rain);
	sceneList.push_back(std::move(scene12));

	for (auto& s : sceneList)
		s->init();

	if (sceneList.size() > 0)
	{
		currentScene = 0;
		sceneList.at(currentScene)->awake();
	}
}

void scene_manager::mainLoop()
{
	t::tick();

	if (currentScene >= 0)
		sceneList.at(currentScene)->mainLoop();

	glutSwapBuffers();
}

void scene_manager::idle()
{
	glutPostRedisplay();
}

void scene_manager::cleanup()
{
	sceneList.clear();
	currentScene = -1;
}

void scene_manager::resize(int width, int height)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->resize(width, height);
}

void scene_manager::normalKeysDown(unsigned char key, int x, int y)
{
	if (key == '+')
		next();

	if (key == '-')
		prev();

	if (key == 'r')
		if (currentScene >= 0)
			sceneList.at(currentScene)->reset();

	if (currentScene >= 0)
		sceneList.at(currentScene)->normalKeysDown(key);
}

void scene_manager::normalKeysUp(unsigned char key, int x, int y)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->normalKeysUp(key);
}

void scene_manager::specialKeys(int key, int x, int y)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->specialKeys(key);
}

void scene_manager::passiveMotion(int x, int y)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->passiveMotion(x, y);
}