#include	"Player.h"

/**
 * �R���X�g���N�^
 */
CPlayer::CPlayer() :
CCharacter() {
}

/**
 * �f�X�g���N�^
 */
CPlayer::~CPlayer(){
	Release();
}

/**
 * �X�V
 */
void CPlayer::Update(void){
	//�L�[���͂ňړ�

	CCharacter::Update();
}