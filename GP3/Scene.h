#pragma once

#include "Common.h"
#include "Model.h"

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

	void AddModel(Model* mesh);
	Model* GetModel(int index);
	Model* GetModel(std::string m_name);
	std::string GetName() { return m_name; }
	std::vector<Model*> GetModels() { return m_models; }

private:
	std::vector<Model*> m_models;
	std::string m_name;
};

