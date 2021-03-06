#define _CRT_SECURE_NO_DEPRECATE

#include "SceneViewer.h"

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#include <glm/glm.hpp> // GLM header files
#include <glm/ext.hpp> // perspective, translate, rotate

#define PIXEL_SCALE 64

// Utils
static char* filetobuf(char* file) {
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); /* Open file for reading */
	if (!fptr) /* Return NULL on failure */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	length = ftell(fptr); /* Find out how many bytes into the file we are */
	buf = (char*)malloc(length + 1); /* Allocate a buffer for the entire length of the file and a
	null terminator */
	fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	fclose(fptr); /* Close the file */
	buf[length] = 0; /* Null terminator */
	return buf; /* Return the buffer */
}

SceneViewer::SceneViewer(std::string windowTitle, float windowWidth, float windowHeight)
{
	width = windowWidth;
	height = windowHeight;

	// SDL Config
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Create the window
	window = new Window(windowTitle, windowWidth, windowHeight);

	// Init OpenGL by defining a context
	context = SDL_GL_CreateContext(window->getWindow());
	// Initialize Glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("Failed to initialize GLAD");
		SDL_Quit();
		return;
	}

	// Generate the Graphics Pipeline Program
	genProgram();

	// Prepare matrices
	// Model Matrix
	this->modelMatrixID = glGetUniformLocation(shaderProgram, "model");

	// View Matrix
	this->viewMatrix = glm::mat4(1.0f);
	// translating the scene in the reverse direction of where we want to move
	this->viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
	// set the view matrix value
	this->viewMatrixID = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, value_ptr(viewMatrix));

	// Projection Matrix
	this->projectionMatrix = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, 0.1f, 100.0f);
	this->projectionMatrixID = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, value_ptr(projectionMatrix));

	glActiveTexture(GL_TEXTURE0); // activate the texture unit
	glBindTexture(GL_TEXTURE_2D, 0);

	// texture uniform
	this->texture1ID = glGetUniformLocation(shaderProgram, "texture1");
	this->textOffset = glGetUniformLocation(shaderProgram, "textOffset");

	/* Enable Z depth testing so objects closest to the viewpoint are in front */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setModelMatrix(glm::mat4(1.0f));
}

SceneViewer::~SceneViewer()
{
	delete window;
}

void SceneViewer::setModelMatrix(glm::mat4 matrix)
{
	glUniformMatrix4fv(this->modelMatrixID, 1, GL_FALSE, value_ptr(matrix));

}

void SceneViewer::setTexture(GLuint texture, float offsetX /*= 0.0f*/, float offsetY /*= 0.0f*/)
{
	glUniform2fv(textOffset, 1, value_ptr(glm::vec2(offsetX, offsetY)));
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(this->texture1ID, 0);
}

void SceneViewer::clear()
{
	/* Make our background black */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneViewer::swapBuffers()
{
	/* Swap our buffers to make our changes visible */
	SDL_GL_SwapWindow(window->getWindow());
}

void SceneViewer::genProgram() {
	GLint IsCompiled_VS, maxLength, IsCompiled_FS, IsLinked;
	char* vertexInfoLog, * fragmentsource, * fragmentInfoLog, * shaderProgramInfoLog;

	////////////////////
	// VERTEX SHADER

	/* Read our shaders into the appropriate buffers */
	char* vertexsource = filetobuf((char*)"shader.vert");
	/* Create an empty vertex shader handle */
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	/* Send the vertex shader source code to GL */
	/* Note that the source code is NULL character terminated. */
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	/* Compile the vertex shader */
	glCompileShader(vertexshader);
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if (IsCompiled_VS == false) {
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);
		/* The maxLength includes the NULL character */
		vertexInfoLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
		/* Handle the error in an appropriate way */
		/* In this simple program, we'll just leave */
		free(vertexInfoLog);
		return;
	}

	////////////////////
	// FRAGMENT SHADER

	/* Read our shaders into the appropriate buffers */
	fragmentsource = filetobuf((char*)"shader.frag");
	/* Create an empty fragment shader handle */
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	/* Send the fragment shader source code to GL */
	/* Note that the source code is NULL character terminated. */
	/* GL will automatically detect that therefore the length info can be 0 in this case (the
	last parameter) */
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	/* Compile the fragment shader */
	glCompileShader(fragmentshader);
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
	if (IsCompiled_FS == false) {
		glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);
		/* The maxLength includes the NULL character */
		fragmentInfoLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);
		/* Handle the error in an appropriate way */
		/* In this simple program, we'll just leave */
		free(fragmentInfoLog);
		return;
	}

	////////////////////
	// PROGRAM

	/* Assign our program handle a "name" */
	shaderProgram = glCreateProgram();

	/* Attach our shaders to our program */
	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);

	/* Attribute locations must be setup before calling glLinkProgram. */
	glBindAttribLocation(shaderProgram, 0, "in_Position");
	glBindAttribLocation(shaderProgram, 1, "in_TexCoord");

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&IsLinked);
	if (IsLinked == false) {
		/* Noticed that glGetProgramiv is used to get the length for a shader program, not
		glGetShaderiv. */
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		/* The maxLength includes the NULL character */
		shaderProgramInfoLog = (char*)malloc(maxLength);
		/* Notice that glGetProgramInfoLog, not glGetShaderInfoLog. */
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength,
			shaderProgramInfoLog);
		/* Handle the error in an appropriate way */
		/* In this simple program, we'll just leave */
		free(shaderProgramInfoLog);
		return;
	}
	/* Load the shader into the rendering pipeline */
	glUseProgram(shaderProgram);

	return;
}