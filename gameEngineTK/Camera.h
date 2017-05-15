//・・・・・・・・・・・・・・・・・・・・・・・・
//カメラを制御するクラス
//・・・・・・・・・・・・・・・・・・・・・・・・

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int Width, int Height);

	virtual ~Camera();

	void Update();

	//ビュー座標を取得
	const DirectX::SimpleMath::Matrix &GetviewMatrix();

	//射影行列を取得
	const DirectX::SimpleMath::Matrix &GetpProjectionMatrix();

	//視点座標をセット
	void SetEyePos(DirectX::SimpleMath::Vector3 eyepos);
	void SetrefPos(DirectX::SimpleMath::Vector3 refpos);
	void SetUpvec(DirectX::SimpleMath::Vector3 upvec);

	//
	void SetFovY(float fovY);
	//
	void SetAspect(float aspect);
	//
	void SetNearClip(float nearclip);
	//
	void SetFarClip(float farclip);


protected:
	//メンバ変数を置くところ
	//ビュー行列
	DirectX::SimpleMath::Matrix m_viewCamera;
	//カメラの位置
	DirectX::SimpleMath::Vector3 m_eyepos;
	//どこを見るのか
	DirectX::SimpleMath::Vector3 m_refpos;
	//上方向ベクトル
	DirectX::SimpleMath::Vector3 m_upvec;
	//射影行列
	DirectX::SimpleMath::Matrix m_projCamera;
	//垂直方向視野
	float m_fovY;
	//画面の横幅を立幅の比率
	float m_aspect;
	//手前の表示限界距離
	float m_nearclip;
	//奥の表示限界距離
	float m_farclip;
};
