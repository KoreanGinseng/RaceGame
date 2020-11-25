#include	"Player.h"

/**
 * コンストラクタ
 */
CPlayer::CPlayer() :
CCharacter() {
}

/**
 * デストラクタ
 */
CPlayer::~CPlayer(){
	Release();
}

/**
 * 更新
 */
void CPlayer::Update(void){
	//キー入力で移動

	CCharacter::Update();
}