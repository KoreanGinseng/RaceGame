#include	"Stage.h"

/**
* コンストラクタ
*/
CStage::CStage() :
m_Mesh() ,
m_SkyMesh() ,
m_Light() {
}

/**
* デストラクタ
*/
CStage::~CStage(){
}

/**
* 読み込み
*/
bool CStage::Load(void){
	// メッシュの読み込み
	if (!m_Mesh.Load("Course1.mom"))
	{
		return false;
	}
	if (!m_SkyMesh.Load("Course1_sky.mom"))
	{
		return false;
	}
	return true;
}

/**
* 初期化
*/
void CStage::Initialize(void){
	//ステージの光源の設定
	m_Light.SetDirection(Vector3(-1, -1, 1));
	m_Light.SetDiffuse(MOF_COLOR_WHITE);
	m_Light.SetAmbient(MOF_COLOR_HWHITE);
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
}

/**
* 更新
*/
void CStage::Update(void){
}

/**
* 描画
*/
void CStage::Render(void){
	// ワールド行列作成
	CMatrix44 matWorld;
	//天球メッシュの描画
	m_SkyMesh.Render(matWorld);
	// メッシュの描画
	m_Mesh.Render(matWorld);
}

/**
* デバッグ文字描画
*/
void CStage::RenderDebugText(void){
}

/**
* 解放
*/
void CStage::Release(void){
	m_Mesh.Release();
	m_SkyMesh.Release();
}