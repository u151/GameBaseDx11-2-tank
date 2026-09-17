#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "TankHead.h"

namespace
{
	XMVECTOR vFront = { 0,0,1,0 };
	const float moveSpeed = 0.1f;
	const float CAM_HEIGHT_BIAS = 0.2f;
	enum CAM_TYPE
	{
		FIXED_CAM,
		TPS_CAM,//タンク
		TPS_CAMROT,
		FPS_CAM,
		CAM_TYPE_MAX
	};

}
Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"),hModel_(-1), camType_(FIXED_CAM)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("Tankbody.fbx");
	assert(hModel_ >= 0);
	Instantiate<TankHead>(this);//親をタンクにして放蕩を生成
}

void Tank::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
		//0,1,2...CAMTYPEMAX-1で切り替える
	}
	switch (camType_)
	{
	case FIXED_CAM:
		SetFixedCam();
		break;
	case TPS_CAM:
	{
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + 3.0f;
		camPos.z = camPos.z - 8.0f;
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
	}
		break;
	case TPS_CAMROT:
	{
		XMFLOAT3 camPos;
		XMVECTOR vCAM = { 0.0f,3.0f,-7.0f,0.0f };
		vCAM = XMVector3TransformCoord(vCAM, matRot);
		XMStoreFloat3(&camPos, vPos + vCAM);
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
	}
		break;
	case FPS_CAM:
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);
		Camera::SetTarget(camTarget);
		break;
	}
		
	

	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 2.0f;
	}
	if (Input::IsKey(DIK_W))
	{
		
		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み（格納）
	}
	if (Input::IsKey(DIK_S))
	{

		vPos = vPos - moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み（格納）
	}
	//例キャストして浮いてたら地面まで落とす
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
	Debug::Log("CAMTYPE = ");
	Debug::Log(camType_, true);//trueは開業するかどうか

	
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}
