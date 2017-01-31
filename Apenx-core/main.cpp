#include "src/graphics/Window.h"
#include "src/graphics/shader/Shader.h"
#include <GLM\glm.hpp>
#include <string>

int main()
{
	using namespace std;
	using namespace apenx;
	using namespace graphics;
	using namespace glm;

	Window window("Apenx! (Test Build 01)", 800, 600);
	glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

	GLuint vbo;

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = ortho();

	Shader shader("src/shaders/shader.vert", "src/shaders/shader.frag");
	shader.enable();

	while (!window.closed())
	{
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.getGLFWWindow(), GL_TRUE);
		}

		window.update();
	}

	return 0;
}