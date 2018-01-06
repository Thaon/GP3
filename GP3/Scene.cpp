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
