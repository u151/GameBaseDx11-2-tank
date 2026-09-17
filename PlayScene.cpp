#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
#include "Engine/SceneManager.h"

int PlayScene::EnemyCount = 0;

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{}

void PlayScene::Initialize()
{
	EnemyCount = 0;

	Instantiate<Ground>(this);
	Instantiate<Tank>(this);

	for (int i = 0; i < 15; i++)
	{
		Instantiate<Enemy>(this);
		EnemyCount++;
	}
}

void PlayScene::Update()
{
	if (EnemyCount <= 0)
	{
		SceneManager* pSceneManager =
			(SceneManager*)GetParent();

		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

void PlayScene::Draw()
{}

void PlayScene::Release()
{}