#include "Actor.h"
#include "Engine.h"
#include "Level.h"
#include "Renderer.h"
#include "SceneViewer.h"

#define SIDE_STEPS 3

static float vertices[4][5] = {
	{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	{ 1.0f, 0.0f, 0.0f, 1.0f / (2.0f * SIDE_STEPS + 1), 1.0f},
	{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
	{ 1.0f, 1.0f, 0.0f, 1.0f / (2.0f * SIDE_STEPS + 1), 0.0f}
};

GLuint vao;
GLuint vbo;
GLuint texture;

Actor::Actor()
{
	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(1, &vao);
	/* Bind our Vertex Array Object as the current used object */
	glBindVertexArray(vao);

	/* Allocate and assign Vertex Buffer Objects to our handle */
	glGenBuffers(1, &vbo);

	/* vertices */
	/* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// TexCoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*SDL_Surface* image = SDL_LoadBMP("../graphics/Ship1.bmp");
	if (image != NULL)
	{
		glGenTextures(1, &this->texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR,
			GL_UNSIGNED_BYTE, image->pixels);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	SDL_FreeSurface(image);*/

	//this->textureOffset = glm::vec2(3.0f * 1.0f / (SIDE_STEPS * 2.0f + 1.0f), 0.0f);

	Engine::getLevel()->addActor(this);
}

void Actor::render(SceneViewer* v)
{
	for (Texture* t : textures)
	{
		//Engine::renderer->copy(t, t->getSrcRect(), t->getDstRect());
	}
}

Actor::~Actor()
{

}
