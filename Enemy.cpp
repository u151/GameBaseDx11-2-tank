#include "Enemy.h"
#include "Engine/Model.h"
#include "Ground.h"
#include "Bullet.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("fbx.fbx");

	Model::SetAnimFrame(hModel_, 1, 100, 1.0f);
	assert(hModel_ >= 0);
	transform_.position_.x = (rand() % 20) - 5.0f;
	transform_.position_.z = (rand() % 20) - 5.0f;
	SphereCollider* collider = new SphereCollider({ 0, 0, 0 }, 0.5f);
	AddCollider(collider);
}

void Enemy::Update()
{
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は０より下に彫られて作られてる　そうじゃないときはさらに上から
	data.dir = { 0,-1,0 };//真下にレイを飛ばす
	Ground* pGround = (Ground*)FindObject("Ground");
	int hGroundModel = pGround->GetModelHandle();//ground
	Model::RayCast(hGroundModel, &data);

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget && pTarget->GetObjectName() == "Bullet")
	{
		pTarget->KillMe();
		KillMe();
	}
}
