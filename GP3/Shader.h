#pragma once
#include "Common.h"

#include "transform.h"
#include "Camera.h"

/***
	The Shader class handles the following:
	- Loading and compiling of external Shaders
	- Binding of the Shader to the OpenGl pipeline
	- Passing game data to the shader (attributes and uniforms)
*/

class Shader
{
public:
	Shader(const std::string& filename);
    ~Shader();

	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera, float deltaTime, float burn);

	std::string Shader::LoadShader(const std::string& fileName);
	void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Shader::CreateShader(const std::string& text, unsigned int type);

	GLuint GetProgram() { return program; }

protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,
		VIEWPROJECTION,
		CAMPOSITION,
		TIME,
		BURNVALUE,
		COLOR,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
	float m_timeElapsed = 0;
};
