#include	"Character.h"

/**
 * コンストラクタ
 */
CCharacter::CCharacter() 
{
}

/**
 * デストラクタ
 */
CCharacter::~CCharacter()
{
}

/**
 * 読み込み
 */
bool CCharacter::Load(void)
{
	// メッシュの読み込み
	m_pMesh     = MeshAsset("Neko");
	m_pBallMesh = MeshAsset("Ball01");
	if (!m_pMesh || !m_pBallMesh)
	{
		return false;
	}
	m_pMotion = m_pMesh->CreateMotionController();
	return true;
}

/**
 * 初期化
 */
void CCharacter::Initialize(void)
{
	m_Pos = Vector3(0.0f, 0.0f, 0.0f);
	m_pMotion->ChangeMotionByName("Stop_Ball", 1.0f, TRUE);

	//カメラの設定
	m_Camera.GetCamera()->SetViewPort();
	m_Camera
		.SetAspect(Vector2(1024.0f, 768.0f))
		.SetNearFar(0.01f, 2000.0f)
		.SetFov(MOF_ToRadian(60.0f));
	m_Camera.Initialize(&m_Camera);
}

/**
 * 更新
 */
void CCharacter::Update(CMeshPtr pGMesh, CMeshPtr pWMesh)
{
	//移動更新
	UpdateMove();

	//ステージと接触判定
	CollisionStage(pGMesh, pWMesh);

	CQuaternion q;
	q.Rotation(m_GroundSlant, m_GroundAxis);
	m_GroundRotationQ.Slerp(m_GroundRotationQ, q, 0.13f);

	//座標更新
	m_Gravity -= GRAVITY;
	m_Pos.y += m_Gravity;
	if (!m_bStage)
	{
		m_Pos += m_Move;
		//移動に合わせてボールの回転を行う
		float r = MOF_MATH_2PI * (m_Move.Length() / CHARACTER_BALLCIRCUMFRENCE);
		CVector3 rv;
		CVector3 nm;
		m_Move.Normal(nm);
		m_GroundNormal.Cross(nm, rv);
		rv.Normal(rv);
		CMatrix33 rmat;
		rmat.RotationAxis(r, rv);
		m_BallRotation *= rmat;
	}

	//アニメーションの時間を進める
	m_pMotion->AddTimer(GAMEFRAMETIME);

	//カメラ更新
	UpdateCamera();
}

/**
 * 移動更新
 */
void CCharacter::UpdateMove(void)
{
	//ブレーキ
	if (m_bBrake)
	{
		float moveLength = m_Move.Length();
		if (moveLength > CHARACTER_BRAKESPEED)
		{
			m_Move.Normal(m_Move);
			m_Move *= (moveLength - CHARACTER_BRAKESPEED);
		}
		else
		{
			m_Move.SetValue(0.0f, 0.0f, 0.0f);
		}
		m_pMotion->ChangeMotionByName("Stop_Ball", 1.0f, TRUE, FALSE);
	}
	//アクセル
	else if(m_bAccele)
	{
		m_pMotion->ChangeMotionByName("Walk_Ball", 1.0f, TRUE, FALSE);
		//移動方向のベクトル
		CVector3 fvec(0, 0, -1);
		CMatrix33 rmat;
		rmat.RotationZXY(m_Angle);
		CMatrix33 matGround;
		m_GroundRotationQ.ConvertMatrixTranspose(matGround);
		rmat *= matGround;
		m_Move += fvec * rmat * CHARACTER_MOVESPEED;
		//移動を最高速度でクリップする
		float moveLength = m_Move.Length();
		if (moveLength >= CHARACTER_MOVESPEEDMAX)
		{
			m_Move.Normal(m_Move);
			m_Move *= CHARACTER_MOVESPEEDMAX;
		}
	}
	//入力なしの場合
	else
	{
		float moveLength = m_Move.Length();
		if (moveLength > CHARACTER_DECELERATIONSPEED)
		{
			m_Move.Normal(m_Move);
			m_Move *= (moveLength - CHARACTER_DECELERATIONSPEED);
		}
		else
		{
			m_Move.SetValue(0.0f, 0.0f, 0.0f);
			m_pMotion->ChangeMotionByName("Stop_Ball", 1.0f, TRUE, FALSE);
		}
	}
	m_bAccele = false;
	m_bBrake = false;
}

/**
 * カメラ更新
 */
void CCharacter::UpdateCamera()
{
	//カメラの設定
	CVector3 cpos = m_Pos;
	CVector3 tpos = m_Pos;
	CVector3 fvec(0, 0, -1);
	fvec.RotationY(m_Angle.y);
	cpos.y += 2.0f;
	cpos   -= fvec * 5.0f;
	tpos.y += 2.0f;
	m_Camera
		.SetPosition(cpos)
		.SetTarget(tpos)
		.SetUpVector(Vector3(0, 1, 0));
}

/**
 * カメラを有効にする
 */
void CCharacter::SetCameraEnable()
{
	CGraphicsUtilities::SetCamera(m_Camera.GetCamera());
}

/**
 * 描画
 */
void CCharacter::Render(void)
{
	//地面の傾斜行列作成
	CMatrix33 matGround;
	m_GroundRotationQ.ConvertMatrixTranspose(matGround);

	// ワールド行列作成
	CMatrix44 matWorld;
	matWorld.RotationZXY(m_Angle);
	matWorld *= matGround;

	CMatrix44 matBallWorld = m_BallRotation;
	matBallWorld *= matGround;
	//ボールを半径分上にあげる
	CVector3 vu{ 0.0f, CHARACTER_BALLRADIUS, 0.0f };
	vu *= matWorld;
	CVector3 vb{ 0.0f, 0.0f, CHARACTER_BALLRADIUS };
	vb *= matWorld;
	//ボールの描画
	matBallWorld.SetTranslation(m_Pos + vu);
	m_pBallMesh->Render(matBallWorld);

	matWorld.SetTranslation(m_Pos + vb);
	//アニメーションにワールドマトリクスを適用
	m_pMotion->RefreshBoneMatrix(matWorld);
	// メッシュの描画
	m_pMesh->Render(m_pMotion);
}

/**
 * デバッグ文字描画
 */
void CCharacter::RenderDebugText(void)
{
	// 位置の描画
	CGraphicsUtilities::RenderString(10,40,MOF_COLOR_WHITE,
			"プレイヤー位置 X : %.1f , Y : %.1f , Z : %.1f",m_Pos.x,m_Pos.y,m_Pos.z);
}

/**
 * 解放
 */
void CCharacter::Release(void)
{
	MOF_SAFE_DELETE(m_pMotion);
	m_pMesh = nullptr;
	m_pBallMesh = nullptr;
}

void CCharacter::CollisionStage(CMeshPtr pGMesh, CMeshPtr pWMesh)
{
	//判定の初期化
	m_bGround = false;
	m_bStage = false;

	//接触情報
	COLLISIONOUTGEOMETRY gout;

	//進行方向へのレイを放つ際の足元からのオフセット値(高さ)
	float offset = 0.5f;
	//進行方向へのレイ
	CRay3D mray{ m_Pos, m_Move };
	mray.Position.y += offset;
	if (mray.CollisionMesh(pWMesh.get(), gout))
	{
		//衝突半径
		float radius = 1.0f;
		if (gout.d <= m_Move.Length() + radius)
		{
			float nd = CVector3Utilities::Dot(m_Move, gout.Normal);
			nd = MOF_ABS(nd);
			m_Move = (m_Move + gout.Normal * -2 * m_Move.Dot(gout.Normal)) * 0.5f;
			m_Pos += mray.Direction * (gout.d - (radius - nd));
			m_Pos += gout.Normal * nd;
			m_bStage = true;
		}
	}

	//下方向へのレイの開始高さ
	float height = 2.0f;
	//下方向へのレイ長さ補正値
	float margin = 0.1f;
	//下方向へのレイ
	CRay3D dray(m_Pos, Vector3(0, -1, 0));
	dray.Position.y += height;
	if (dray.CollisionMesh(pGMesh.get(), gout))
	{
		if (gout.d <= height + margin)
		{
			m_Pos.y += (height + margin) - gout.d;
			m_Gravity = 0.0f;
			m_bGround = true;

			//地面の傾斜角度と傾斜軸を求める
			CVector3 upv(0, 1, 0);
			m_GroundSlant = upv.DotAngle(gout.Normal);
			upv.Cross(gout.Normal, m_GroundAxis);
			m_GroundNormal = gout.Normal;
			m_GroundAxis.Normal(m_GroundAxis);
		}
	}
}
