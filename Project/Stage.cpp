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
	m_pMesh = nullptr;
	m_pSkyMesh = nullptr;
	m_pCollisionWallMesh = nullptr;
	m_pCollisionGroundMesh = nullptr;
}

CMeshPtr CStage::GetCollisionGroundMesh(void)
{
	return m_pCollisionGroundMesh;
}

CMeshPtr CStage::GetCollisionWallMesh(void)
{
	return m_pCollisionWallMesh;
}
