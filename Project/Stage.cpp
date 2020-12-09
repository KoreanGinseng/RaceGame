#include	"Stage.h"

/**
* コンストラクタ
*/
CStage::CStage()
{
}

/**
* デストラクタ
*/
CStage::~CStage()
{
}

/**
* 読み込み
*/
bool CStage::Load(void)
{
	// メッシュの読み込み
	m_pMesh    = MeshAsset("Course1");
	m_pSkyMesh = MeshAsset("Course1_sky");
	m_pCollisionWallMesh   = MeshAsset("Course1WallHit");
	m_pCollisionGroundMesh = MeshAsset("Course1GroundHit");
	if (!m_pMesh || !m_pSkyMesh || !m_pCollisionWallMesh || !m_pCollisionGroundMesh)
	{
		return false;
	}

	//テキストファイルを開く
	FILE* fp = fopen("path.txt", "rt");
	if (fp == NULL)
	{
		return false;
	}

	//スタート地点読み込み
	for (int i = 0; i < MAXCHARACTER; i++)
	{
		fscanf(fp, "%f,%f,%f\n", &m_StartPos[i].x, &m_StartPos[i].y, &m_StartPos[i].z);
	}
	//パス読み込み
	fscanf(fp, "%d\n", &m_PathCount);
	m_PathArray = new CVector3[m_PathCount];
	for (int i = 0; i < m_PathCount; i++)
	{
		fscanf(fp, "%f,%f,%f\n", &m_PathArray[i].x, &m_PathArray[i].y, &m_PathArray[i].z);
	}
	//ファイルを閉じる
	fclose(fp);

	return true;
}

/**
* 初期化
*/
void CStage::Initialize(void)
{
	//ステージの光源の設定
	m_Light.SetDirection(Vector3(-1, -1, 1));
	m_Light.SetDiffuse(MOF_COLOR_WHITE);
	m_Light.SetAmbient(MOF_COLOR_HWHITE);
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

/**
* 更新
*/
void CStage::Update(void)
{
}

/**
* 描画
*/
void CStage::Render(void)
{
	// ワールド行列作成
	CMatrix44 matWorld;
	//天球メッシュの描画
	m_pSkyMesh->Render(matWorld);
	// メッシュの描画
	m_pMesh->Render(matWorld);
}

/**
* デバッグ描画
*/
void CStage::RenderDebug(void)
{
	//パス地点描画
	for (int i = 0; i < m_PathCount; i++)
	{
		CSphere gsp{ m_PathArray[i], 3.0f };
		CGraphicsUtilities::RenderSphere(gsp, CVector4{ 0, 1, 0, 0.5f });
		//次の点とを線でつなぐ
		if (i != m_PathCount - 1)
		{
			CGraphicsUtilities::RenderLine(m_PathArray[i], m_PathArray[i + 1], MOF_COLOR_GREEN);
		}
	}
}

/**
* デバッグ文字描画
*/
void CStage::RenderDebugText(void)
{
}

/**
* 解放
*/
void CStage::Release(void)
{
	m_pMesh                = nullptr;
	m_pSkyMesh             = nullptr;
	m_pCollisionWallMesh   = nullptr;
	m_pCollisionGroundMesh = nullptr;
	MOF_SAFE_DELETE_ARRAY(m_PathArray);
}

const CVector3 & CStage::GetStartPos(int no) const
{
	return m_StartPos[no];
}

CVector3 * CStage::GetPath(void)
{
	return m_PathArray;
}

int CStage::GetPathCount(void)
{
	return m_PathCount;
}

CMeshPtr CStage::GetCollisionGroundMesh(void)
{
	return m_pCollisionGroundMesh;
}

CMeshPtr CStage::GetCollisionWallMesh(void)
{
	return m_pCollisionWallMesh;
}
