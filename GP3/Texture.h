#pragma once
#include "Common.h"

/***
	This class is just used as a container for OpenGL related texture data
*/

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

