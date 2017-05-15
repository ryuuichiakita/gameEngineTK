#include "Camera.h"

using namespace DirectX;
using namespace SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera(int Width,int Height)
{
	//�����o�ϐ��̏�����
	m_eyepos=Vector3(0, 0, 1.0f);
	m_refpos = Vector3(0, 1, 0);
	m_upvec = Vector3(0, 0, 1);
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
	m_viewCamera = Matrix::Identity;


	//�ˉe�s��𐶐�
	m_projCamera = Matrix::Identity;

}

Camera::~Camera()
{

}

void Camera::Update()
{
	m_viewCamera = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	m_projCamera = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

Matrix Camera::GetviewMatrix()
{
	return m_viewCamera;
}

Matrix Camera::GetpProjectionMatrix()
{
	return m_projCamera;
}

void Camera::SetEyePos(Vector3 eyepos)
{
	m_eyepos = eyepos;
}
