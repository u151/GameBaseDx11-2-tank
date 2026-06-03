#include "PlayScene.h"
#include "Ground.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")	
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);//親をplaysceneにして地面を生成
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
