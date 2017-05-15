#include "Camera.h"

using namespace DirectX;
using namespace SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera(int Width,int Height)
{
	//�����o�ϐ��̏�����
	m_eyepos=Vector3(0, 0, 5.0f);
	m_refpos = Vector3(0, 0, 0);
	m_upvec = Vector3(0, 1, 0);
	m_upvec.Normalize();

	//������������
	m_fovY = XMConvertToRadians(60.0f);
	//��ʂ̉����𗧕��̔䗦
	m_aspect = (float)Width / Height;
	//��O�̕\�����E����
	m_nearclip = 0.1f;
	//���̕\�����E����
	m_farclip = 1000.0f;
	
	//�r���[�s��𐶐�
	m_viewCamera = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//�ˉe�s��𐶐�
	m_projCamera = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

Camera::~Camera()
{

}

void Camera::Update()
{
	m_viewCamera = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	m_projCamera = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

const Matrix & Camera::GetviewMatrix()
{
	return m_viewCamera;
}

const Matrix & Camera::GetpProjectionMatrix()
{
	return m_projCamera;
}

void Camera::SetEyePos(Vector3 eyepos)
{
	m_eyepos = eyepos;
}

void Camera::SetrefPos(Vector3 refpos)
{
	m_refpos = refpos;
}

void Camera::SetUpvec(Vector3 upvec)
{
	m_upvec = upvec;
}

void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}
