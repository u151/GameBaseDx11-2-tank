#include "Ground.h"
#include "Engine/Model.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent,"Ground"), hModel_(-1)
{
}//

Ground::~Ground()
{
}

void Ground::Initialize()
{
	//モデルの読み込み
	hModel_ = Model::Load("Ground.fbx");
	assert(hModel_ >= 0);
}

void Ground::Update()
{
}

void Ground::Draw()
{
	//transformのデフォ値
	//scale_ {1,1,1}
	//rotate_ {0,0,0}
	//
	Model::SetTransform(hModel_, transform_);
}

void Ground::Release()
{
}
