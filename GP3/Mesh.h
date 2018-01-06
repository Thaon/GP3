#pragma once

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "transform.h"

/***
	The Vertex class holds information about position, uv coordinates and normals
*/

struct Vertex
{
public:
	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }
	glm::vec3* GetColor() { return &color; }

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec3 color;
};

/***
	The Mesh class has all the information required by OpenGl to draw its polygons.
	It also contains a vector of textures, this particular vector is only used if during the model loading, the Mesh's internal textures are used.
*/

class Mesh {
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	/*  Functions  */
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	void OnlyDrawMesh(Shader shader);
private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;
	/*  Functions    */
	void SetupMesh();
};

