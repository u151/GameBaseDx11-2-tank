#include "TestScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Text.h"

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{}

void TestScene::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();
}

void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* sceneManager =
			dynamic_cast<SceneManager*>(GetParent());
		sceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw()
{
	std::string scrText;
	scrText = "TestScene";
	pText_->Draw(20, 20, scrText.c_str());
}

void TestScene::Release()
{}
