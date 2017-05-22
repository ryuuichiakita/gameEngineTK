#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
const float FollowCamera::CAMERA_DISTANCE = 5.0f;


FollowCamera::FollowCamera(int width, int height)
	: Camera(width, height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	isFPS = false;
	InitializeTPS();
}

void FollowCamera::Update()
{
	Vector3 eyepos, refpos;

	//キーボードの状態を取得
	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboardTracker.Update(keystate);

	//Cキーを押したら
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		//フラグを切り替え
		isFPS = !isFPS;
		if (!isFPS)
		{
			InitializeTPS();
		}
	}

	if (isFPS)
	{ 
		Vector3 position;
		position = m_targetPos + Vector3(0, 0.2f, 0);
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV * 0.1f;
		refpos = position + cameraV;
	}
	else
	{ 
		refpos = m_targetPos + Vector3(0, 2, 0);
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = refpos + cameraV;
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
		refpos = m_refpos + (refpos - m_refpos) * 0.20f;
	}

	SetEyePos(eyepos);
	SetrefPos(refpos);
	//基底クラスの更新
	Camera::Update();
	//m_view = m_Camera->GetviewMatrix();
	//m_proj = m_Camera->GetpProjectionMatrix();

}
void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	//自機の上方２ｍの位置を捉える
	refpos = m_targetPos + Vector3(0, 2, 0);
	//参照点から視点への差分
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);
	//自機の後ろに回り込むための回転
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	//差分ベクトルを回転させる
	cameraV = Vector3::TransformNormal(cameraV, rotmat);
	//視点座標を計算
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetrefPos(refpos);
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_targetPos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
