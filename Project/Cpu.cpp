#include "Cpu.h"

void CCpu::Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3 * path, int cnt)
{
	//パス最大数以上の通過が確認されたらゴールと判定してキー入力は行わない
	if (m_PathNo >= cnt - 1)
	{
		CCharacter::Update(pGMesh, pWMesh, path, cnt);
		return;
	}
	//今の点から次の点へ向かうベクトルと今の位置から次の点へ向かうベクトルの中間を使用して判定
	CVector3 npv = path[m_PathNo + 1] - path[m_PathNo];
	CVector3 ncv = path[m_PathNo + 1] - m_Pos;
	CVector3 nv  = (npv + ncv) * 0.5f;
	nv.Normal(nv);
	//縦の移動は無視する
	nv.y = 0.0f;

	//自分の前方ベクトル
	CVector3 mv{ 0, 0, -1 };
	mv.RotationY(m_Angle.y);

	//現在の進行ベクトルと内積から角度を求める
	float da = nv.DotAngle(mv);

	//２次元ベクトルの外積を求めて、左右どちらかにいるのかを判定する
	float dy = nv.z * mv.x - nv.x * mv.z;

	//キー入力で移動の代わり
	if (dy > 0)
	{
		//コース進路より右側にいるので、左にキー入力したことにする
		m_Angle.y -= CHARACTER_ROTATIONSPEED;
		MOF_NORMALIZE_RADIANANGLE(m_Angle.y);
	}
	else if (dy < 0)
	{
		//コース進路より左側にいるので、右にキー入力したことにする
		m_Angle.y += CHARACTER_ROTATIONSPEED;
		MOF_NORMALIZE_RADIANANGLE(m_Angle.y);
	}

	//目標との角度が大きくなればブレーキ、それ以外は常にアクセル
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
