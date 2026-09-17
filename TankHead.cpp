#include "TankHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Bullet.h"

TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "TankHead"), hModel_(-1)
{
}


void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void TankHead::Update()
{
	
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2.0f;
	}
	if (Input::IsKey(DIK_UP))
	{
		transform_.rotate_.x -= 2.0f;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		transform_.rotate_.x += 2.0f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		const float BULLET_SPEED = 0.3f;

		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");
		//①XMVectorに二つとも変換
		//②vMoveを作って単位ベクトル化
		//③スピード0.2f
		//④XMFLOAT3にもどして
		// ① XMVectorに二つとも変換

		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);

		// ② vMoveを作って単位ベクトル化
		XMVECTOR vMove = vTop - vRoot;

		// ③ スピード0.2f
		vMove = BULLET_SPEED * vMove;

		// ④ XMFLOAT3にもどして
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		pBullet->SetMoveVector(move);//④からとってくる
		pBullet->SetPosition(cannonTop);
	}
}

void TankHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{

}
