#include <iostream>
#include "MainGame.h"

#include "TestGO.h"

int main(int argc, char** argv) //argument used to call SDL main
{
	//create and configure game
	MainGame mainGame;
	int width = 1200;
	int height = 600;
	mainGame.InitDisplay(width, height, glm::vec4(0.7f, 0.7f, 0.7f,1));

	
	//Load models and textures, if using false on the UseInternalTextures parameter
	//TestGO nano;
	//nano.InitModel("Tree", "res/Tree/tree.obj", true);
	//nano.AddExternalTexture("res/tree/treetex.png");

	/*Model monkey("monkey", "../res/monkey3.obj", false);
	monkey.AddExternalTexture("../res/bricks.jpg");
	monkey.AddExternalTexture("../res/Water.jpg");
	
	Model alien("Alien", "../res/Hominid/alienhominid.obj", true);*/

	//Load in the shader
	Shader toonShader("res/shader"); //toon shader

	//bind the shader to the models
	//nano.SetShader(&burnshader);

	//create camera and set it as the main active one
	Camera cam;
	cam.initCamera(glm::vec3(0, 0, 0), 70.0f, float(width / height), 0.01f, 1000.0f);
	mainGame.SetActiveCamera(&cam);

	//create scene and add models
	SceneManager::CreateScene("Scene1");
	SceneManager::GetActiveScene()->LoadFromFile("res/Level.txt");
	
	//set up shader for each model
	for (auto model : SceneManager::GetActiveScene()->GetModels())
	{
		model->SetShader(&toonShader);
		std::cout << model->GetColliderRadius() << std::endl;
	}

	//cam.SetPosition(glm::vec3(7,5,-3));
	//cam.LookAt(*SceneManager::GetActiveScene()->GetModel("Tree")->GetTransform().GetPos());

	//SceneManager::GetActiveScene()->AddModel(&nano);

	//finally run game
	mainGame.run();

	return 0;
}