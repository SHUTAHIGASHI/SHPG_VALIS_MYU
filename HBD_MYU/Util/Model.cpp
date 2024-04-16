#include "Model.h"

Model::Model():
	m_hModel(-1),
	m_AnimNo(-1),
	m_AnimIndex(0),
	m_AnimTotalTime(0.0f),
	m_AnimPlayTime(0.0f),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_rotation(VGet(0.0f, 0.0f, 0.0f))
{
}

Model::~Model()
{
	// ���f���n���h���폜
	MV1DeleteModel(m_hModel);
}

void Model::Init(int hModel)
{
	// ���f���n���h�����
	m_hModel = hModel;
}

void Model::Update()
{
	// �Đ����Ԃ�i�߂�
	m_AnimPlayTime += 1.0f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (m_AnimPlayTime > m_AnimTotalTime)
	{
		m_AnimPlayTime = 0.0f;
	}

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(m_hModel, m_AnimIndex, m_AnimPlayTime);
}

void Model::Draw()
{
	// ���f���`��
	MV1DrawModel(m_hModel);
}

void Model::SetPosition(VECTOR pos)
{
	// ���W�ݒ�
	m_pos = pos;
	MV1SetPosition(m_hModel, m_pos);
}

void Model::SetScale(float size)
{
	// �g�嗦�ݒ�
	MV1SetScale(m_hModel, VGet(size, size, size));
}

void Model::SetMotionType(int motionType)
{
	// ���s���郂�[�V�����ݒ�
	if (m_AnimNo == motionType) return;
	m_AnimNo = motionType;
	m_AnimIndex = MV1AttachAnim(m_hModel, motionType, -1);
	m_AnimTotalTime = MV1GetAttachAnimTotalTime(m_hModel, m_AnimIndex);
	m_AnimPlayTime = 0.0f;
}

void Model::SetDirection(VECTOR lookPos, float rota)
{
	// �����ݒ�
	lookPos.y -= 500.0f;
	MV1SetRotationZYAxis(m_hModel, VGet(0.0f, 0.0f, 1.0f), VSub(m_pos, lookPos), rota);
}

void Model::SetRotation(VECTOR rota)
{
	// ��]�����ݒ�
	m_rotation = rota;
	MV1SetRotationXYZ(m_hModel, m_rotation);
}
