#include "DrawingPrisms.h"


DrawingPrisms::DrawingPrisms(vector<Prism> prismsVector, int polygonNumber)
{
	srand(time(NULL)); // to draw lots color value
	this->polygonNumber = polygonNumber;
	for (Prism prism : prismsVector)
	{
		vector<GLfloat> tmpVerticesVector;
		Polygon polygon = prism.getBase();
		int verticesNumber = 0;
		for (Vertex v : polygon.getVerticesList())
		{
			tmpVerticesVector.push_back((GLfloat)v.getX());
			tmpVerticesVector.push_back((GLfloat)v.getY());
			tmpVerticesVector.push_back((GLfloat)0.0f);
			++verticesNumber;
		}
		verticesNumbers.push_back(verticesNumber);
		verticesLists.push_back(tmpVerticesVector);
		
	}
}

void DrawingPrisms::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void DrawingPrisms::drawPrisms(const char* windowName)
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
	}
	else
	{
		// opengl wersja 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		try
		{
			// tworzymy okno - dwa ostatnie argumenty - mniej wazne ale jesli w pierwszym ustawimy glfwGetPrimaryMonitor() to bedziemy mieli okno na caly ekran
			GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, windowName, nullptr, nullptr);
			if (window == nullptr)
				throw exception("GLFW window not created");
			glfwMakeContextCurrent(window); // kontekst naszego okienka glownym kontekstem w aktualnym watku
			glfwSetKeyCallback(window, key_callback); // rejestrujemy ta funkcje "nasluchiwania" przycisków klawy

			glewExperimental = GL_TRUE; // wiecej nowoczesnych technik do opengl
			if (glewInit() != GLEW_OK)
				throw exception("GLEW Initialization failed");

			glViewport(0, 0, WIDTH, HEIGHT); // okno renderingu

			ShaderProgram ourShader("shader.vert", "shader.frag");

			GLuint VAO;
			glGenVertexArrays(1, &VAO);
			GLuint VBO;
			glGenBuffers(1, &VBO);

			vector<glm::vec3> colors;
			for (int i = 0; i < polygonNumber; ++i)
			{
				colors.push_back(glm::vec3(fRand(0.0f, 1.0f), fRand(0.0f, 1.0f), fRand(0.0f, 1.0f)));
			}

			glLineWidth(2.0f);

			while (!glfwWindowShouldClose(window))
			{

				glfwPollEvents();

				glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // kolor
				glClear(GL_COLOR_BUFFER_BIT);

				ourShader.Use();

				glm::mat4 view;
				glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 90.0f); // polozenie kamery
				glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // na co patrzy kamera
				view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 projection;
				//projection = glm::perspective(0.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.0f, 100.0f);
				projection = glm::ortho(-90.0f, 90.0f, -90.0f, 90.0f, 0.0f, 100.0f);
				GLint viewLoc = glGetUniformLocation(ourShader.get_programID(), "view");
				GLint projLoc = glGetUniformLocation(ourShader.get_programID(), "projection");
				glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

				GLint colorLoc = glGetUniformLocation(ourShader.get_programID(), "ourColor");
			
				glBindVertexArray(VAO);

				for (int i = 0; i < polygonNumber; ++i)
				{
					glUniform3f(colorLoc, colors[i].x, colors[i].y, colors[i].z);

					GLfloat* vertices = new GLfloat[verticesNumbers[i] * 3];

					for (int j = 0; j < verticesNumbers[i] * 3; ++j)
						vertices[j] = verticesLists[i][j];					

					glBindBuffer(GL_ARRAY_BUFFER, VBO);
					glBufferData(GL_ARRAY_BUFFER, verticesNumbers[i] * 3 * sizeof(vertices), vertices, GL_STATIC_DRAW);

					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
					glEnableVertexAttribArray(0);

					glDrawArrays(GL_LINE_LOOP, 0, verticesNumbers[i]);

					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

				glBindVertexArray(0);

				glfwSwapBuffers(window);
			}

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
		catch (exception ex)
		{
			cout << ex.what() << endl;
		}
		glfwTerminate();
	}
}

GLfloat DrawingPrisms::fRand(GLfloat fMin, GLfloat fMax)
{
	GLfloat f = (GLfloat)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

DrawingPrisms::~DrawingPrisms()
{
}
