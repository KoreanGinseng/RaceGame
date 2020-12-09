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
	m_pShadow   = MeshAsset("Shadow");
	if (!m_pMesh || !m_pBallMesh)
	{
		return false;
	}
	m_pMotion = m_pMesh->CreateMotionController();
	return true;
}

/**
 * 初期化
 * [in]      sp      開始位置
 * [in]      path    パス
 */
void CCharacter::Initialize(const CVector3& sp, CVector3* path)
{
	//開始地点の設定と最初のパスの向きにキャラを向ける
	m_Pos = sp;
	m_Angle.y = atan2f(path[1].z - path[0].z, -(path[1].x - path[0].x)) + MOF_MATH_HALFPI;
	m_PathNo = 0;
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
void CCharacter::Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3 * path, int cnt)
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

	// 影の描画
	CMatrix44 matShadow;

	//ボールの影
	matShadow.Scaling(2.0f);
	matShadow *= matGround;
	matShadow.SetTranslation(m_Pos + m_GroundNormal * 0.01f);
	m_pShadow->Render(matShadow);

	//キャラクタの影
	matShadow.Scaling(1.0f);
	matShadow *= matGround;
	matShadow.SetTranslation(m_Pos + vb + m_GroundNormal * 0.01f);
	m_pShadow->Render(matShadow);
}

/**
 * デバッグ文字描画
 */
void CCharacter::RenderDebugText(void)
{
	// 位置の描画
	CGraphicsUtilities::RenderString(10,40,MOF_COLOR_WHITE,
			"プレイヤー位置 X : %.1f , Y : %.1f , Z : %.1f / %d [順位 %d]",
		m_Pos.x,m_Pos.y,m_Pos.z, m_PathNo, m_Rank);
}

/**
 * 解放
 */
void CCharacter::Release(void)
{
	MOF_SAFE_DELETE(m_pMotion);
	m_pMesh     = nullptr;
	m_pBallMesh = nullptr;
	m_pShadow   = nullptr;
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

void CCharacter::CalculatePathNo(CVector3 * path, int cnt)
{
	//現在のパス位置から順に判定
	for (int i = m_PathNo; i < cnt; i++)
	{
		//最後の一転はゴールとして前の点とで判定
		if (i == cnt - 1)
		{
			//現在の点から前の点へ向かうベクトル
			CVector3 nv = path[i] - path[i - 1];
			//現在の点からキャラクターへ向かうベクトル
			CVector3 cv = m_Pos - path[i];
			//二つのベクトルの内積が＋なら最後の点は通過済みとする
			if (nv.Dot(cv) > 0.0f)
			{
				//最後の点のため＋１してすべての点を通過済みとする
				m_PathNo = i + 1;
			}
			else
			{
				break;
			}
		}
		else
		{
			//現在の点から次の点へ向かうベクトル
			CVector3 nv = path[i + 1] - path[i];
			//現在の点からキャラクターへ向かうベクトル
			CVector3 cv = m_Pos - path[i];
			//二つのベクトルの内積が＋なら現在の点は通過済みとする
			if (nv.Dot(cv) > 0.0f)
			{
				m_PathNo = i;
			}
			else
			{
				//違う場合は現在の点を未通過として判定終了
				break;
			}
		}
	}
}

void CCharacter::UpdateRank(CCharacter** chara, int ccnt, CVector3 * path, int cnt)
{
	//パス最大数以上の通過が確認されたらゴールと判定して順位の更新は行わない
	if(m_PathNo >= cnt - 1)
	{ 
		return;
	}

	//初期値設定
	m_Rank = 1;
	//全キャラと判定
	for (int i = 0; i < ccnt; i++)
	{
		//通過パス番号が相手のほうが大きいと相手のほうが前
		if (chara[i]->m_PathNo > m_PathNo)
		{
			m_Rank++;
		}
		//通過パス番号が同じなら次の通過パスへの距離が近いほうが前
		else if (chara[i]->m_PathNo == m_PathNo)
		{
			//次の点から今の点へのベクトル
			CVector3 nv = path[m_PathNo] - path[m_PathNo + 1];
			//次の点から自分へのベクトル
			CVector3 pv = m_Pos - path[m_PathNo + 1];
			//次の点から判定キャラへのベクトル
			CVector3 ov = chara[i]->m_Pos - path[m_PathNo + 1];
			if (nv.Dot(pv) > nv.Dot(ov))
			{
				m_Rank++;
			}
		}
	}
}
