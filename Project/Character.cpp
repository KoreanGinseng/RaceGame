#include	"Character.h"

/**
 * �R���X�g���N�^
 */
CCharacter::CCharacter() 
{
}

/**
 * �f�X�g���N�^
 */
CCharacter::~CCharacter()
{
}

/**
 * �ǂݍ���
 */
bool CCharacter::Load(void)
{
	// ���b�V���̓ǂݍ���
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
 * ������
 * [in]      sp      �J�n�ʒu
 * [in]      path    �p�X
 */
void CCharacter::Initialize(const CVector3& sp, CVector3* path)
{
	//�J�n�n�_�̐ݒ�ƍŏ��̃p�X�̌����ɃL������������
	m_Pos = sp;
	m_Angle.y = atan2f(path[1].z - path[0].z, -(path[1].x - path[0].x)) + MOF_MATH_HALFPI;
	m_PathNo = 0;
	m_pMotion->ChangeMotionByName("Stop_Ball", 1.0f, TRUE);

	//�J�����̐ݒ�
	m_Camera.GetCamera()->SetViewPort();
	m_Camera
		.SetAspect(Vector2(1024.0f, 768.0f))
		.SetNearFar(0.01f, 2000.0f)
		.SetFov(MOF_ToRadian(60.0f));
	m_Camera.Initialize(&m_Camera);
}

/**
 * �X�V
 */
void CCharacter::Update(CMeshPtr pGMesh, CMeshPtr pWMesh, CVector3 * path, int cnt)
{
	//�ړ��X�V
	UpdateMove();

	//�X�e�[�W�ƐڐG����
	CollisionStage(pGMesh, pWMesh);

	CQuaternion q;
	q.Rotation(m_GroundSlant, m_GroundAxis);
	m_GroundRotationQ.Slerp(m_GroundRotationQ, q, 0.13f);

	//���W�X�V
	m_Gravity -= GRAVITY;
	m_Pos.y += m_Gravity;
	if (!m_bStage)
	{
		m_Pos += m_Move;
		//�ړ��ɍ��킹�ă{�[���̉�]���s��
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

	//�A�j���[�V�����̎��Ԃ�i�߂�
	m_pMotion->AddTimer(GAMEFRAMETIME);

	//�J�����X�V
	UpdateCamera();
}

/**
 * �ړ��X�V
 */
void CCharacter::UpdateMove(void)
{
	//�u���[�L
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
	//�A�N�Z��
	else if(m_bAccele)
	{
		m_pMotion->ChangeMotionByName("Walk_Ball", 1.0f, TRUE, FALSE);
		//�ړ������̃x�N�g��
		CVector3 fvec(0, 0, -1);
		CMatrix33 rmat;
		rmat.RotationZXY(m_Angle);
		CMatrix33 matGround;
		m_GroundRotationQ.ConvertMatrixTranspose(matGround);
		rmat *= matGround;
		m_Move += fvec * rmat * CHARACTER_MOVESPEED;
		//�ړ����ō����x�ŃN���b�v����
		float moveLength = m_Move.Length();
		if (moveLength >= CHARACTER_MOVESPEEDMAX)
		{
			m_Move.Normal(m_Move);
			m_Move *= CHARACTER_MOVESPEEDMAX;
		}
	}
	//���͂Ȃ��̏ꍇ
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
 * �J�����X�V
 */
void CCharacter::UpdateCamera()
{
	//�J�����̐ݒ�
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
 * �J������L���ɂ���
 */
void CCharacter::SetCameraEnable()
{
	CGraphicsUtilities::SetCamera(m_Camera.GetCamera());
}

/**
 * �`��
 */
void CCharacter::Render(void)
{
	//�n�ʂ̌X�΍s��쐬
	CMatrix33 matGround;
	m_GroundRotationQ.ConvertMatrixTranspose(matGround);

	// ���[���h�s��쐬
	CMatrix44 matWorld;
	matWorld.RotationZXY(m_Angle);
	matWorld *= matGround;

	CMatrix44 matBallWorld = m_BallRotation;
	matBallWorld *= matGround;
	//�{�[���𔼌a����ɂ�����
	CVector3 vu{ 0.0f, CHARACTER_BALLRADIUS, 0.0f };
	vu *= matWorld;
	CVector3 vb{ 0.0f, 0.0f, CHARACTER_BALLRADIUS };
	vb *= matWorld;
	//�{�[���̕`��
	matBallWorld.SetTranslation(m_Pos + vu);
	m_pBallMesh->Render(matBallWorld);

	matWorld.SetTranslation(m_Pos + vb);
	//�A�j���[�V�����Ƀ��[���h�}�g���N�X��K�p
	m_pMotion->RefreshBoneMatrix(matWorld);
	// ���b�V���̕`��
	m_pMesh->Render(m_pMotion);

	// �e�̕`��
	CMatrix44 matShadow;

	//�{�[���̉e
	matShadow.Scaling(2.0f);
	matShadow *= matGround;
	matShadow.SetTranslation(m_Pos + m_GroundNormal * 0.01f);
	m_pShadow->Render(matShadow);

	//�L�����N�^�̉e
	matShadow.Scaling(1.0f);
	matShadow *= matGround;
	matShadow.SetTranslation(m_Pos + vb + m_GroundNormal * 0.01f);
	m_pShadow->Render(matShadow);
}

/**
 * �f�o�b�O�����`��
 */
void CCharacter::RenderDebugText(void)
{
	// �ʒu�̕`��
	CGraphicsUtilities::RenderString(10,40,MOF_COLOR_WHITE,
			"�v���C���[�ʒu X : %.1f , Y : %.1f , Z : %.1f / %d",m_Pos.x,m_Pos.y,m_Pos.z, m_PathNo);
}

/**
 * ���
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
	//����̏�����
	m_bGround = false;
	m_bStage = false;

	//�ڐG���
	COLLISIONOUTGEOMETRY gout;

	//�i�s�����ւ̃��C����ۂ̑�������̃I�t�Z�b�g�l(����)
	float offset = 0.5f;
	//�i�s�����ւ̃��C
	CRay3D mray{ m_Pos, m_Move };
	mray.Position.y += offset;
	if (mray.CollisionMesh(pWMesh.get(), gout))
	{
		//�Փ˔��a
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

	//�������ւ̃��C�̊J�n����
	float height = 2.0f;
	//�������ւ̃��C�����␳�l
	float margin = 0.1f;
	//�������ւ̃��C
	CRay3D dray(m_Pos, Vector3(0, -1, 0));
	dray.Position.y += height;
	if (dray.CollisionMesh(pGMesh.get(), gout))
	{
		if (gout.d <= height + margin)
		{
			m_Pos.y += (height + margin) - gout.d;
			m_Gravity = 0.0f;
			m_bGround = true;

			//�n�ʂ̌X�Ίp�x�ƌX�Ύ������߂�
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
	//���݂̃p�X�ʒu���珇�ɔ���
	for (int i = m_PathNo; i < cnt; i++)
	{
		//�Ō�̈�]�̓S�[���Ƃ��đO�̓_�ƂŔ���
		if (i == cnt - 1)
		{
			//���݂̓_����O�̓_�֌������x�N�g��
			CVector3 nv = path[i] - path[i - 1];
			//���݂̓_����L�����N�^�[�֌������x�N�g��
			CVector3 cv = m_Pos - path[i];
			//��̃x�N�g���̓��ς��{�Ȃ�Ō�̓_�͒ʉߍς݂Ƃ���
			if (nv.Dot(cv) > 0.0f)
			{
				//�Ō�̓_�̂��߁{�P���Ă��ׂĂ̓_��ʉߍς݂Ƃ���
				m_PathNo = i + 1;
			}
			else
			{
				break;
			}
		}
		else
		{
			//���݂̓_���玟�̓_�֌������x�N�g��
			CVector3 nv = path[i + 1] - path[i];
			//���݂̓_����L�����N�^�[�֌������x�N�g��
			CVector3 cv = m_Pos - path[i];
			//��̃x�N�g���̓��ς��{�Ȃ猻�݂̓_�͒ʉߍς݂Ƃ���
			if (nv.Dot(cv) > 0.0f)
			{
				m_PathNo = i;
			}
			else
			{
				//�Ⴄ�ꍇ�͌��݂̓_�𖢒ʉ߂Ƃ��Ĕ���I��
				break;
			}
		}
	}
}
