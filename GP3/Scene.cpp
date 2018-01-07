#include "Scene.h"



Scene::Scene(std::string name)
{
	m_name = name;
	m_models = std::vector<Model*>();
}

Scene::Scene()
{
	m_name = "default name";
	m_models = std::vector<Model*>();
}


Scene::~Scene()
{
}

void Scene::LoadFromFile(std::string filename)
{
	//open the file and read all lines in memory
	std::vector<std::string> levelLines;

	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			levelLines.push_back(line);
		}
		file.close();
	}
	else
	{
		std::cout << "could not open level" << std::endl;
		return;
	}
	//go through the lines, create and customise objects
	for (auto line : levelLines)
	{
		//
	}

}

void Scene::AddModel(Model * mesh)
{
	m_models.push_back(mesh);
}

Model* Scene::GetModel(int index)
{
	if (m_models.size() > index)
		return m_models.at(index);
	else
	{
		std::cout << "not enough models in the scene!" << std::endl;
		return nullptr;
	}
}

Model* Scene::GetModel(std::string name)
{
	for (auto model : m_models)
	{
		if (model->GetName() == name)
			return model;
	}
	std::cout << "could not find model named: " << name << std::endl;
	return nullptr;
}
