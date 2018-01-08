#pragma once

#include "Common.h"
#include "Model.h"
#include "StaticModel.h"
#include "TestGO.h"
#include "CameraPlaceholder.h"

#include <fstream>
#include <sstream>

/***
	The Scene class offers a way to manage models in a structured way.
	It essentially is just a collection of references to Models that are imported in the game (preferably in the main function).
	It provides methods to operate on the vector of pointers to models and is usually accessed in the MainGame.cpp to perform operations of models such as:
	- Pass Transform information to Shaders
	- Draw the Meshes
*/

class Scene
{
public:
	Scene(std::string name);
	Scene();
	~Scene();

	void LoadFromFile(std::string filename);
	void AddModel(Model* mesh);
	Model* GetModel(int index);
	Model* GetModel(std::string m_name);
	std::string GetName() { return m_name; }
	std::vector<Model*> &GetModels() { return m_models; }

private:
	std::vector<Model*> m_models;
	std::string m_name;

	//String split taken from: https://stackoverflow.com/questions/5167625/splitting-a-c-stdstring-using-tokens-e-g
	std::vector<std::string> Split(const std::string& s, char seperator)
	{
		std::vector<std::string> output;

		std::string::size_type prev_pos = 0, pos = 0;

		while ((pos = s.find(seperator, pos)) != std::string::npos)
		{
			std::string substring(s.substr(prev_pos, pos - prev_pos));

			output.push_back(substring);

			prev_pos = ++pos;
		}

		output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

		return output;
	}
};