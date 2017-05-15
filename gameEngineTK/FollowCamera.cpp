#include "pch.h"
#include "FollowCamera.h"

using namespace std;
using namespace DirectX::SimpleMath;
const float FollowCamera::CAMERA_DISTANCE = 5.0f;


FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	m_targetPos = (Vector3::Zero);
	m_targetAngle = 0.0f;
}


FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update()
{
	//視点、参照点
	Vector3 eyepos, refpos;

	//ターゲットの座標は、自機の座標に追従（ちょっと上に）
	refpos = m_targetPos + Vector3(0, 2.0f, 0);
	//ターゲット座標からカメ座標への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);

	//
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetrefPos(refpos);

	//基底クラスの更新
	Camera::Update();
	//m_view = m_Camera->GetviewMatrix();
	//m_proj = m_Camera->GetpProjectionMatrix();

}

void FollowCamera::SetTargetpos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_targetPos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetAngle)
{
	m_targetAngle = targetAngle;
}
