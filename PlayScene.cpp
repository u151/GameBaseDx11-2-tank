#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")	
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);//親をplaysceneにして地面を生成
	Instantiate<Tank>(this);
	for (int i = 0; i < 10; i++) {
		Instantiate<Enemy>(this);
	}
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
