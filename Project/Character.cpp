#include	"Character.h"

/**
 * コンストラクタ
 */
CCharacter::CCharacter() :
m_Mesh() ,
m_pMotion(NULL) ,
m_Pos() ,
m_Move() ,
m_Angle() ,
m_Camera() ,
m_bAccele(false),
m_bBrake(false) {
}

/**
 * デストラクタ
 */
CCharacter::~CCharacter(){
}

/**
 * 読み込み
 */
bool CCharacter::Load(void){
	// メッシュの読み込み
	if(!m_Mesh.Load("Neko.mom"))
	{
		return false;
	}
	m_pMotion = m_Mesh.CreateMotionController();
	return true;
}

/**
 * 初期化
 */
void CCharacter::Initialize(void){
	m_Pos = Vector3(0.0f,0.0f,0.0f);
	m_pMotion->ChangeMotionByName("Stop_Ball", 1.0f, TRUE);

	//カメラの設定
	m_Camera.SetViewPort();
	m_Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
	UpdateCamera();
}

/**
 * 更新
 */
void CCharacter::Update(void){
	//移動更新
	UpdateMove();

	//座標更新
	m_Pos += m_Move;

	//アニメーションの時間を進める
	m_pMotion->AddTimer(GAMEFRAMETIME);

	//カメラ更新
	UpdateCamera();
}

/**
 * 移動更新
 */
void CCharacter::UpdateMove(void){
	//ブレーキ

	//アクセル

	//入力なしの場合

}

/**
 * カメラ更新
 */
void CCharacter::UpdateCamera(){
	//カメラの設定
	CVector3 cpos = m_Pos;
	CVector3 tpos = m_Pos;
	CVector3 fvec(0, 0, -1);
	fvec.RotationY(m_Angle.y);
	cpos.y += 2.0f;
	cpos -= fvec * 5.0f;
	tpos.y += 2.0f;
	m_Camera.LookAt(cpos, tpos, CVector3(0, 1, 0));
	m_Camera.Update();
}

/**
 * カメラを有効にする
 */
void CCharacter::SetCameraEnable(){
	CGraphicsUtilities::SetCamera(&m_Camera);
}

/**
 * 描画
 */
void CCharacter::Render(void){
	// ワールド行列作成
	CMatrix44 matWorld;
	matWorld.RotationZXY(m_Angle);
	matWorld.SetTranslation(m_Pos);
	//アニメーションにワールドマトリクスを適用
	m_pMotion->RefreshBoneMatrix(matWorld);
	// メッシュの描画
	m_Mesh.Render(m_pMotion);
}

/**
 * デバッグ文字描画
 */
void CCharacter::RenderDebugText(void){
	// 位置の描画
	CGraphicsUtilities::RenderString(10,40,MOF_COLOR_WHITE,
			"プレイヤー位置 X : %.1f , Y : %.1f , Z : %.1f",m_Pos.x,m_Pos.y,m_Pos.z);
}

/**
 * 解放
 */
void CCharacter::Release(void){
	MOF_SAFE_DELETE(m_pMotion);
	m_Mesh.Release();
}