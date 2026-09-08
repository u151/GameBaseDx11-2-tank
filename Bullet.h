#pragma once
#include "Engine/GameObject.h"
class Bullet : public GameObject
{
	//コンストラクタ
//引数：parent  親オブジェクト（SceneManager）
public:
	Bullet(GameObject* parent);
	~Bullet() {}

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetMoveVector(XMFLOAT3 move) { move_ = move; }//玉の進行方向セット
private:
	int hModel_;//地面モデルのハンドル
	XMFLOAT3 move_;//玉の進行方向
};

