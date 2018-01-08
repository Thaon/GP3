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
	for (auto model : m_models)
	{
		delete model;
	}
	m_models.clear();
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
		Model* mod;

		std::vector<std::string> sections = Split(line, '~');

		//check the type based on name
		std::string objName = Split(sections[1], ',')[0];
		std::cout << "Creating object: " << objName << std::endl;

		if (objName == "Player")
			mod = new TestGO;
		else if (objName == "Camera")
			mod = new CameraPlaceholder();
		else
			mod = new StaticModel();


		//0 is the object type
		if (sections[0] == "obj")
		{
			//1 is the name and location of the model
			std::vector<std::string> modelSections = Split(sections[1], ',');
			mod->InitModel(modelSections[0], (GLchar*)modelSections[1].c_str(), true);

			//2 is position
			std::vector<std::string> position = Split(sections[2], ',');
			mod->GetTransform().SetPos(glm::vec3(std::stof(position[0]), std::stof(position[1]), std::stof(position[2])));

			//3 is rotation
			std::vector<std::string> rotation = Split(sections[3], ',');
			mod->GetTransform().SetRotation(glm::vec3(std::stof(rotation[0]), std::stof(rotation[1]), std::stof(rotation[2])));

			//4 is scaling
			std::vector<std::string> scaling = Split(sections[4], ',');
			mod->GetTransform().SetScale(glm::vec3(std::stof(scaling[0]), std::stof(scaling[1]), std::stof(scaling[2])));

			//5 is the collider
			mod->SetupCollisions(std::stof(sections[5]));

			//add to active scene
			AddModel(mod);
		}
		else if (sections[0] == "cam")
		{
			mod->SetName("Camera");
			mod->m_isCamera = true;
			//2 is position
			std::vector<std::string> position = Split(sections[2], ',');
			mod->GetTransform().SetPos(glm::vec3(std::stof(position[0]), std::stof(position[1]), std::stof(position[2])));

			//3 is rotation
			std::vector<std::string> rotation = Split(sections[3], ',');
			mod->GetTransform().SetRotation(glm::vec3(std::stof(rotation[0]), std::stof(rotation[1]), std::stof(rotation[2])));

			//add to active scene
			AddModel(mod);
		}
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
