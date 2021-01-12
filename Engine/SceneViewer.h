#pragma once
#include "Window.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class SceneViewer
{
	int width;
	int height;

	Window* window = nullptr;
	SDL_GLContext context;

	GLuint shaderProgram = -1;

	// vertex
	GLint modelMatrixID = -1;
	GLint viewMatrixID = -1;
	GLint projectionMatrixID = -1;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	// fragment
	GLint texture1ID = -1;
	GLint textOffset = -1;

	void genProgram();

public:
	SceneViewer(std::string windowTitle, int windowWidth, int windowHeight);
	~SceneViewer();

	void setModelMatrix(glm::mat4 matrix);
	void setTexture(GLuint texture, glm::vec2* textureOffset = nullptr);

	void clear();
	void swapBuffers();

	Window* getWindow() { return window; };
};

