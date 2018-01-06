#include "Model.h"


void Model::Draw(Shader shader)
{
	if (m_useInternalTextures)
	{
		for (GLuint i = 0; i < this->meshes.size(); i++)
			meshes[i].Draw(shader);
	}
	else
	{
		GLuint diffuseNr = 1;
		for (GLuint i = 0; i < this->meshes.size(); i++)
		{
			for (GLuint j = 0; j < this->m_loadedTextures.size(); j++)
			{
				std::string number = std::to_string(m_loadedTextures[j].id);
				glUniform1i(glGetUniformLocation(shader.GetProgram(), ("texture_diffuse" + number).c_str()), j);
				glActiveTexture(GL_TEXTURE0 + j); // Activate proper texture unit before binding
												  // Retrieve texture number (the N in diffuse_textureN)
				glBindTexture(GL_TEXTURE_2D, this->m_loadedTextures[j].id);
			}


			meshes[i].OnlyDrawMesh(shader);
		}
	}
}

void Model::SetShader(Shader* shader)
{
	m_shader = shader;
}

void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	std::cout << "Loaded model: " << path << std::endl;

	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}


void Model::processNode(aiNode * node, const aiScene * scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // Positions
		if (mesh->mVertices->Length() > 0)
		{
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.pos = vector;
		}
		// Normals
		if (mesh->mNormals !=  nullptr)
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}
		// Texture Coordinates
		if (mesh->mTextureCoords != nullptr) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = vec;
		}
		//vertex color
		for (int j = 0; j < AI_MAX_NUMBER_OF_COLOR_SETS; j++)
		{
			if (mesh->HasVertexColors(j))
			{
				std::cout << "Vertex color set found at index " << j << std::endl;
			}
		}
		if (mesh->mColors[0] != NULL)
		{
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
			if (mat != nullptr)
			{
				std::cout << "found material, processing color" << std::endl;
				aiColor3D color(0.f, 0.f, 0.f);
				mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);

				vector.x = color.r;
				vector.y = color.g;
				vector.z = color.b;
				vertex.color = vector;
			}
		}
		else
			vertex.texCoord = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++) // from: http://stackoverflow.com/questions/31683310/assimp-not-loading-correctly
	{
		aiFace face = mesh->mFaces[i];
		if (face.mNumIndices < 3) {
			continue;
		}
		assert(face.mNumIndices == 3);
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// Process materials
	if (m_useInternalTextures && mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		GLboolean skip = false;
		for (GLuint j = 0; j < m_loadedTextures.size(); j++)
		{
			if (std::strcmp(m_loadedTextures[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(m_loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			std::cout << "found texture: " << str.C_Str() << " of type: " << typeName << std::endl;
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
			this->m_loadedTextures.push_back(texture);  // Add to loaded textures
		}
	}
	return textures;
}

GLint Model::TextureFromFile(const char * path, std::string directory)
{
	//Generate texture ID and load texture data 
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (image != nullptr)
		std::cout << "loaded: " << path << std::endl;
	else
		std::cout << "could not load: " << path << std::endl;
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}

void Model::AddExternalTexture(std::string dir)
{
	GLuint textureID;
	glActiveTexture(GL_TEXTURE0 + m_loadedTextures.size() - 1);
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(dir.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (image != nullptr)
		std::cout << "loaded: " << dir << ", with texture ID: " << textureID << std::endl;
	else
		std::cout << "could not load: " << dir << std::endl;
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	Texture texture;
	texture.id = textureID;
	texture.path = dir;
	this->m_loadedTextures.push_back(texture);  // Add to loaded textures
}

void Model::SetupCollisions(float radius)
{
	if (radius > 0)
	{
		m_calculateCollisions = true;
		m_colliderRadius = radius;
	}
}
