#include "Tank.h"
#include "Engine/Model.h"

Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"),hModel_(-1)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("Tankbody.fbx");
	assert(hModel_ >= 0);
}

void Tank::Update()
{
}

void Tank::Draw()
{
}

void Tank::Release()
{
}
