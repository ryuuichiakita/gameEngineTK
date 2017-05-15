#include "Camera.h"

using namespace DirectX;
using namespace SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera(int Width,int Height)
{
	//メンバ変数の初期化
	m_eyepos=Vector3(0, 0, 1.0f);
	m_refpos = Vector3(0, 1, 0);
	m_upvec = Vector3(0, 0, 1);
	m_upvec.Normalize();

	//垂直方向視野
	m_fovY = XMConvertToRadians(60.0f);
	//画面の横幅を立幅の比率
	m_aspect = (float)Width / Height;
	//手前の表示限界距離
	m_nearclip = 0.1f;
	//奥の表示限界距離
	m_farclip = 1000.0f;
	
	//ビュー行列を生成
	m_viewCamera = Matrix::Identity;


	//射影行列を生成
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
