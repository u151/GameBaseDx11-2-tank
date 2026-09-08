#include "Bullet.h"
#include "Engine/Model.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hModel_(-1)
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
	Collider* collider = new SphereCollider({0, 0, 0},0.25f);
	AddCollider(collider);
}

void Bullet::Update()
{
	//transform_.position_ = transform_.position_ + move
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	move_.y -= 0.005f;
	XMVECTOR vMove = XMLoadFloat3(&move_);
	vPos = vPos + vMove;
	XMStoreFloat3(&transform_.position_, vPos);
	//transform_.position.x += move_.x;
	//transform_.position.y += move_.y;
	//transform_.position.z += move_.z;
	if (transform_.position_.y < -20.0f||transform_.position_.y > 20.0f)
	{
		KillMe();
	}
}

//玉の弾道を重力つける
//敵を配置　（敵もレイキャストしてXZ座標ランダムで置く）とりあえず一匹
//当たり判定（コライダーの設置）

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
