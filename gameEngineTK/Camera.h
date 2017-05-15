//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�J�����𐧌䂷��N���X
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int Width, int Height);

	virtual ~Camera();

	void Update();

	//�r���[���W���擾
	DirectX::SimpleMath::Matrix GetviewMatrix();

	//�ˉe�s����擾
	DirectX::SimpleMath::Matrix GetpProjectionMatrix();

	//���_���W���Z�b�g
	void SetEyePos(DirectX::SimpleMath::Vector3 eyepos);


protected:
	//�����o�ϐ���u���Ƃ���
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_viewCamera;
	//�J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_eyepos;
	//�ǂ�������̂�
	DirectX::SimpleMath::Vector3 m_refpos;
	//������x�N�g��
	DirectX::SimpleMath::Vector3 m_upvec;
	//�ˉe�s��
	DirectX::SimpleMath::Matrix m_projCamera;
	//������������
	float m_fovY;
	//��ʂ̉����𗧕��̔䗦
	float m_aspect;
	//��O�̕\�����E����
	float m_nearclip;
	//���̕\�����E����
	float m_farclip;
};
