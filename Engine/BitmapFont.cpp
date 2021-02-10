#include "BitmapFont.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Transform.h"
#include "SceneViewer.h"

static Transform* pos;

BitmapFont::BitmapFont()
{
	//Initialize variables
	bitmap = nullptr;
	tilemap = nullptr;
	newLine = 0;
	if (pos == nullptr)
		pos = new Transform;
}

void BitmapFont::buildFont(Texture* fontBitmap, int rows, int cols)
{
	bitmap = fontBitmap;
	tilemap = new Tilemap(fontBitmap, rows, cols);

	// Set new line to slightly taller than a character
	newLine = -(tilemap->getTileHeight() + 1);
}

void BitmapFont::drawText(float x, float y, std::string text, SceneViewer* v)
{
	// If the bitmap has been built
	if (bitmap != NULL) {
		// Character offsets
		pos->setPosition(x, y);
		float curX = x, curY = y;//
		
		// Go through the text
		for (int i = 0; i < text.length(); ++i) {
			// If the current character is a newline
			if (text[i] == '\n') {
				// Move down and back
				//pos->setPosition(x, curY + newLine);
				pos->Translate(x-curX, newLine);
				curY += newLine;//
				curX += x-curX;//
			}
			else {
				// Get the ASCII value of the character minus 32 because we don't have the first 32 characters
				int ascii = text[i]-32;

				// Render the character
				tilemap->ChangeFrame(ascii);

				v->setModelMatrix(pos->getGlmTransform());
				bitmap->draw(v);

				// SDL Render
				//Engine::renderer->copy(bitmap, bitmap->getSrcRect(), bitmap->getDstRect());

				//Move over the width of one character + 1 for padding
				//pos->setPosition(curX += tilemap->getTileWidth(), curY);
				pos->Translate(tilemap->getTileWidth(), 0.0f);
				curX += tilemap->getTileWidth();//
			}
		}
	}
}


/*void BitmapFont::renderText(GLfloat x, GLfloat y, std::string text)
{
	//If there is a texture to render from
	//if (getTextureID() != 0)
	{
		//Draw positions
		GLfloat dX = x;
		GLfloat dY = y;

		//Move to draw position
		glTranslatef(x, y, 0.f);

		//Set texture
		glBindTexture(GL_TEXTURE_2D, getTextureID());

		//Enable vertex and texture coordinate arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//Bind vertex data
		glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBuffer);

		//Set texture coordinate data
		glTexCoordPointer(2, GL_FLOAT, sizeof(LVertexData2D), (GLvoid*)offsetof(LVertexData2D, texCoord));

		//Set vertex data
		glVertexPointer(2, GL_FLOAT, sizeof(LVertexData2D), (GLvoid*)offsetof(LVertexData2D, position));

		//Go through string
		for (int i = 0; i < text.length(); ++i)
		{
			//Space
			if (text[i] == ' ')
			{
				glTranslatef(mSpace, 0.f, 0.f);
				dX += mSpace;
			}
			//Newline
			else if (text[i] == '\n')
			{
				glTranslatef(x - dX, mNewLine, 0.f);
				dY += mNewLine;
				dX += x - dX;
			}
			//Character
			else
			{
				//Get ASCII
				GLuint ascii = (unsigned char)text[i];

				//Draw quad using vertex data and index data
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[ascii]);
				glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

				//Move over
				glTranslatef(mClips[ascii].w, 0.f, 0.f);
				dX += mClips[ascii].w;
			}
		}
	}
}*/