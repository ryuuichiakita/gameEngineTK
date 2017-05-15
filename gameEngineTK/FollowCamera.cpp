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
	//���_�A�Q�Ɠ_
	Vector3 eyepos, refpos;

	//�^�[�Q�b�g�̍��W�́A���@�̍��W�ɒǏ]�i������Ə�Ɂj
	refpos = m_targetPos + Vector3(0, 2.0f, 0);
	//�^�[�Q�b�g���W����J�����W�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);

	//
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetrefPos(refpos);

	//���N���X�̍X�V
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
