/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

#ifndef DRAWINGPRISMS_H
#define DRAWINGPRISMS_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM - do matematyki
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <time.h>
#include "shprogram.h"
#include "Prism.h"

using namespace std;

class DrawingPrisms
{
private:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;
	vector<vector<GLfloat>> verticesLists;
	int polygonNumber;
	vector<int> verticesNumbers;

	static void DrawingPrisms::key_callback(GLFWwindow*, int, int, int, int);
	static GLfloat fRand(GLfloat, GLfloat);
public:
	DrawingPrisms(vector<Prism>, int);
	~DrawingPrisms();
	void drawPrisms(const char*);
protected:
private:
};

#endif // DRAWINGPRISMS_H
