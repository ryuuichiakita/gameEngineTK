/// <summary>
/// é©ã@Ç…í«è]Ç∑ÇÈÉJÉÅÉâ
/// </summary>

#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
public:
	const static float CAMERA_DISTANCE;
	FollowCamera(int width,int height);
	~FollowCamera();

	void Update();

	void SetTargetpos(const DirectX::SimpleMath::Vector3& targetpos);
	void SetTargetAngle(float targetAngle);

protected:
	DirectX::SimpleMath::Vector3 m_targetPos;
	float m_targetAngle;


};

