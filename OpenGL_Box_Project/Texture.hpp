#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

// Other Libs
#include "SOIL2/SOIL2.h"


class Texture {
public:
	GLuint TextureId;
	GLuint Index;

	Texture(const GLchar *texturePath)
	{
		Index = 0;
		// --== TEXTURE == --
		glGenTextures(1, &TextureId);
		glBindTexture(GL_TEXTURE_2D, TextureId); 
		// All upcoming GL_TEXTURE_2D operations now have effect on our texture object
		// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Load, create texture and generate mipmaps
		int width, height;
		unsigned char *image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		// Unbind texture when done, so we won't accidentily mess up our texture.
		glBindTexture(GL_TEXTURE_2D, 0);
	}
private:

};
