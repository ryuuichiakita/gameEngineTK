#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;

	m_sinAngle = 0.0f;

	Initialize();
}

Player::~Player()
{
}
/// <summary>
/// 初期化処理☆彡
/// </summary>
void Player::Initialize()
{
	//自機パーツのロード
	m_Obj.resize(PARTS_NUM);
	m_Obj[PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_Obj[PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_Obj[PARTS_ENGINE].LoadModel(L"Resources/engine1.cmo");
	m_Obj[PARTS_FAN].LoadModel(L"Resources/fan.cmo");
	m_Obj[PARTS_GARD].LoadModel(L"Resources/gard.cmo");

	//親子関係の構築（子供に親をセット）
	m_Obj[PARTS_BASE].SetObjParent(
		&m_Obj[PARTS_BODY]);

	m_Obj[PARTS_GARD].SetObjParent(
		&m_Obj[PARTS_BASE]);

	m_Obj[PARTS_ENGINE].SetObjParent(
		&m_Obj[PARTS_BODY]);

	m_Obj[PARTS_FAN].SetObjParent(
		&m_Obj[PARTS_BODY]);

	//親からのオフセット（ローカルの座標ずれ）
	m_Obj[PARTS_BODY].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_BASE].SetTranslation(
		Vector3(0, 0.7f, 0));

	m_Obj[PARTS_GARD].SetTranslation(
		Vector3(0.7, 1.0f, 0));
	m_Obj[PARTS_GARD].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_ENGINE].SetTranslation(
		Vector3(0.22f, 0.3f, 0.22f));

	m_Obj[PARTS_FAN].SetTranslation(
		Vector3(0, 0.3f, 1.0f));

	con=0;
}
/// <summary>
/// 更新処理（　＾ω＾）・・・
/// </summary>
void Player::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	////自機の角度を変動
	//Vector3 angle;  
	//自機パーツのギミック
	{
		//angle = m_Obj[PARTS_GARD].GetRotation();
		//m_Obj[PARTS_GARD].SetRotation(
		//	angle + Vector3(0.2f, 0.1f, 0));

		//サインの引数の角度がだんだん増える
		m_sinAngle += 0.1f;
		//ファンの角度がいったりきたりする(-1～+1)
		float fan_angle = sinf(m_sinAngle) * 3.0f;
	}

	//Aキーを押している間
	if (keystate.A)
	{
		//自機の角度を変動
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(
			Vector3(0, angle + 0.03f, 0));
	}

	//Dキーを押している間
	if (keystate.D)
	{
		//自機の角度を変動
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(
			Vector3(0, angle - 0.03f, 0));
	}

	//Wキーを押している間
	if (keystate.W)
	{
		//移動ベクトル
		Vector3 moveV(0, 0, -0.1f);
		//今の角度に合わせて移動ベクトルを回転
		//回転行列
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動
		Vector3 pos = m_Obj[0].GetTranslation();
		pos += moveV;
		m_Obj[0].SetTranslation(pos);
	}

	//Sキーを押している間
	if (keystate.S)
	{
		//移動ベクトル
		Vector3 moveV(0, 0, +0.1f);
		//回転行列
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動
		Vector3 pos = m_Obj[0].GetTranslation();
		pos += moveV;
		m_Obj[0].SetTranslation(pos);
	}

	//弾丸が進む処理
	{
		//自機の座標を移動
		Vector3 pos = m_Obj[PARTS_GARD].GetTranslation();
		pos += m_BulletVel;
		m_Obj[PARTS_GARD].SetTranslation(pos);
	}

	//ファイアーであります
	con++;
	if (keystate.Space)
	{
		FireBullet();
	}
	if (keystate.Z)
	{
		if (con > 20)
		{
			m_Obj[PARTS_GARD].SetObjParent(
				&m_Obj[PARTS_BASE]);
			m_BulletVel = Vector3(0, 0, 0);
			m_Obj[PARTS_GARD].SetTranslation(
				Vector3(0.7f, 1.0f, 0));
			m_Obj[PARTS_GARD].SetScale(
				Vector3(2, 2, 2));
			con = 0;
		}
	}

	//行列更新
	Calc();
}
/// <summary>
/// 行列更新（　＾ω＾）・・・
/// </summary>
void Player::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Update();
	}
}
/// <summary>
/// 描画（　＾ω＾）・・・
/// </summary>
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Draw();
	}
}

void Player::FireBullet()
{
	//ワールド行列を取得
	Matrix worldm = m_Obj[PARTS_GARD].GetWorld();

	Vector3 scale;	//ワールドスケーリング
	Quaternion rotation;	//ワールド回転
	Vector3 translation;	//ワールド座標

	//ワールド行列から各要素を取り出す
	worldm.Decompose(scale, rotation, translation);

	//親子関係を解除してパーツを独立させる
	m_Obj[PARTS_GARD].SetObjParent(nullptr);
	m_Obj[PARTS_GARD].SetScale(scale);
	m_Obj[PARTS_GARD].SetRotationQ(rotation);
	m_Obj[PARTS_GARD].SetTranslation(translation);

	//弾の速度を設定
	m_BulletVel = Vector3(0, 0, -0.3f);
	//弾の向きに合わせて進行方向を回転
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);
}

const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	//タンクパーツの座標を返す
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Player::GetRot()
{
	//タンクパーツの座標を返す
	return m_Obj[0].GetRotation();
}

void Player::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	//タンクパーツの座標を設定
	m_Obj[0].SetTranslation(trans);
}

void Player::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	//タンクパーツの座標を設定
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Player::GetLocalWorld()
{
	//タンクパーツのワールド行列を返す
	return m_Obj[0].GetWorld();
}
