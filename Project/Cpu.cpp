#include "Cpu.h"

void CCpu::Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3 * path, int cnt)
{
	//�p�X�ő吔�ȏ�̒ʉ߂��m�F���ꂽ��S�[���Ɣ��肵�ăL�[���͍͂s��Ȃ�
	if (m_PathNo >= cnt - 1)
	{
		CCharacter::Update(pGMesh, pWMesh, path, cnt);
		return;
	}
	//���̓_���玟�̓_�֌������x�N�g���ƍ��̈ʒu���玟�̓_�֌������x�N�g���̒��Ԃ��g�p���Ĕ���
	CVector3 npv = path[m_PathNo + 1] - path[m_PathNo];
	CVector3 ncv = path[m_PathNo + 1] - m_Pos;
	CVector3 nv  = (npv + ncv) * 0.5f;
	nv.Normal(nv);
	//�c�̈ړ��͖�������
	nv.y = 0.0f;

	//�����̑O���x�N�g��
	CVector3 mv{ 0, 0, -1 };
	mv.RotationY(m_Angle.y);

	//���݂̐i�s�x�N�g���Ɠ��ς���p�x�����߂�
	float da = nv.DotAngle(mv);

	//�Q�����x�N�g���̊O�ς����߂āA���E�ǂ��炩�ɂ���̂��𔻒肷��
	float dy = nv.z * mv.x - nv.x * mv.z;

	//�L�[���͂ňړ��̑���
	if (dy > 0)
	{
		//�R�[�X�i�H���E���ɂ���̂ŁA���ɃL�[���͂������Ƃɂ���
		m_Angle.y -= CHARACTER_ROTATIONSPEED;
		MOF_NORMALIZE_RADIANANGLE(m_Angle.y);
	}
	else if (dy < 0)
	{
		//�R�[�X�i�H��荶���ɂ���̂ŁA�E�ɃL�[���͂������Ƃɂ���
		m_Angle.y += CHARACTER_ROTATIONSPEED;
		MOF_NORMALIZE_RADIANANGLE(m_Angle.y);
	}

	//�ڕW�Ƃ̊p�x���傫���Ȃ�΃u���[�L�A����ȊO�͏�ɃA�N�Z��
	if (da > MOF_MATH_HALFPI * 0.5f)
	{
		m_bBrake = true;
	}
	else
	{
		m_bAccele = true;
	}

	CCharacter::Update(pGMesh, pWMesh, path, cnt);
}
