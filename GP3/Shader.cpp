#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& filename)
{
	program = glCreateProgram(); // create shader program (openGL saves as ref number)
	shaders[0] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER); // create vertex shader
	shaders[1] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]); //add all our shaders to the shader program "shaders" 
	}

	glBindAttribLocation(program, 0, "position"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(program, 1, "normal");
	glBindAttribLocation(program, 2, "texCoord");
	glBindAttribLocation(program, 3, "color");


	glLinkProgram(program); //create executables that will run on the GPU shaders
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(program); //check the entire program is valid
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "MVP"); // associate with the location of uniform variable within a program
	uniforms[MODELMATRIX] = glGetUniformLocation(program, "modelMatrix");
	uniforms[CAMPOSITION] = glGetUniformLocation(program, "camPos");
	uniforms[TIME] = glGetUniformLocation(program, "time");
	uniforms[LIGHTDIR] = glGetUniformLocation(program, "lightDir");
	uniforms[INTENSITY] = glGetUniformLocation(program, "lightIntensity");
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the sahders
	}
	glDeleteProgram(program); // delete the program
}

void Shader::Bind()
{
	glUseProgram(program); //installs the program object specified by program as part of rendering state
}

void Shader::Update(const Transform& transform, const Camera& camera, float deltaTime, float burn)
{
	m_timeElapsed += deltaTime;
	glm::vec3 cameraPosition = camera.GetPosition();
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glm::mat4 model = transform.GetModel();
	//glm::mat4 camPos = camera.GetViewProjection();

	glm::vec3 lightPosition = glm::vec3(45, 45, 0);

	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(uniforms[MODELMATRIX], 1, GLU_FALSE, &model[0][0]);
	glUniform3fv(uniforms[CAMPOSITION], 1, &cameraPosition[0]);
	//glUniform1f(uniforms[TIME], m_timeElapsed);
	glUniform3fv(uniforms[LIGHTDIR], 1, &lightPosition[0]);
	glUniform1f(uniforms[INTENSITY], 1);
}


GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	std::cout << "Shader creation process completed" << std::endl;

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

