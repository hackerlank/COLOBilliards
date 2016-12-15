///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shadow.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Shadow.h"
#include "Scene.h"
#include "Manager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shadow::Shadow(int nPriority):Scene(nPriority)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �f�X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shadow::~Shadow()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̏���������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Shadow::Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel)
{	
	LPDIRECT3DDEVICE9 pDevice = Manager::GetRenderer()->GetDevice();
	
	OBJ_TYPE=2;//��ʂ�ǂɐݒ�

	D3DXLoadMeshFromX(pModel,
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&m_pBuffMat,
						NULL,
						&m_numMat,
						&m_pMesh);
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);
	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//���W
	m_aVertex[0].pos = D3DXVECTOR3(0,0,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		
	m_aVertex[0].rhw = 1.0f;
	m_aVertex[1].rhw = 1.0f;
	m_aVertex[2].rhw = 1.0f;
	m_aVertex[3].rhw = 1.0f;
	
	//�F���
	m_aVertex[0].col = D3DCOLOR_RGBA(1,1,1,120);
	m_aVertex[1].col = D3DCOLOR_RGBA(1,1,1,120);
	m_aVertex[2].col = D3DCOLOR_RGBA(1,1,1,120);
	m_aVertex[3].col = D3DCOLOR_RGBA(1,1,1,120);

	m_aVertex[0].tex = D3DXVECTOR2(0.0f/* ���WU */,0.0f /* ���WV */ );
	m_aVertex[1].tex = D3DXVECTOR2(1.0f/* ���WU */,0.0f /* ���WV */ );
	m_aVertex[2].tex = D3DXVECTOR2(0.0f/* ���WU */,1.0f /* ���WV */ );
	m_aVertex[3].tex = D3DXVECTOR2(1.0f/* ���WU */,1.0f /* ���WV */ );
		
	m_pVtxBuff->Unlock();
		
	//�e�N�X�`���ǂݍ���
	m_pTexture = pTexture;
	m_pos = pos;
	m_rot = rot;
	m_scl = scl*0.6f;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̏I������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::Uninit(void)
{
	if(m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	
	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	Release();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̍X�V����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::Update(void)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̕`�揈��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrancelate;
	
	// �}�e���A�����ւ̃|�C���^�ϐ�
	D3DXMATERIAL *pMat;

	// ���݂̃}�e���A�������ꎞ�ۑ�����ϐ�
	D3DMATERIAL9 matDef;

	// �f�o�C�X�I�u�W�F�N�g�̊m��
	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���[���h�}�g���b�N�X�̍쐬
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);

	// �傫���𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// �����𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrancelate, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrancelate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);




	//�X�e���V���e�X�g��L��
	pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
	//Z�o�b�t�@�ւ̏������݂𖳌���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	//�J���[�o�b�t�@�ւ̏������݂𖳌���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0);


	///////////////////////////////////////////////////////////////////
	// �X�e���V���ݒ�1
	///////////////////////////////////////////////////////////////////

	//�X�e���V���e�X�g�ɑS�Ă����i������
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);
	//�X�e���V���e�X�g���i�AZ�e�X�g���i�̏ꍇ0�ɂ���
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);
	//�X�e���V���e�X�g���i�AZ�e�X�g�s���i�̏ꍇ�C���N�������g
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);
	//�X�e���V���e�X�g�s���i�̏ꍇ0�ɂ���
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);
	//�J�����O���t�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
	//�e���f���̕`��
	
	// ���݂̃}�e���A���̈ꎞ�ۑ�
	pDevice->GetMaterial(&matDef);

	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	// �}�e���A���̐������[�v
	for (int nCntMat = 0; nCntMat < (int)m_numMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);


		if(pMat[nCntMat].pTextureFilename)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// �e�p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�������̏�Ԃɖ߂�
	pDevice->SetMaterial(&matDef);

	//�X�e���V���Q�ƒl"1"�ɂ���
	pDevice->SetRenderState(D3DRS_STENCILREF,1);

	///////////////////////////////////////////////////////////////////
	// �X�e���V���ݒ�2
	///////////////////////////////////////////////////////////////////
	
	//�X�e���V���Q�ƒl�ȏ�ō��i
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_GREATEREQUAL);
	//�X�e���V���e�X�g���i�AZ�e�X�g���i�̏ꍇ�C���N�������g
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);
	//�X�e���V���e�X�g���i�AZ�e�X�g�s���i�̏ꍇ0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);
	//�X�e���V���e�X�g�s���i�̏ꍇ0�ɂ���
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);
	//�J�����O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	//�e���f���̕`��
	
	// ���݂̃}�e���A���̈ꎞ�ۑ�
	pDevice->GetMaterial(&matDef);

	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	// �}�e���A���̐������[�v
	for (int nCntMat = 0; nCntMat < (int)m_numMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);


		if(pMat[nCntMat].pTextureFilename)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// �e�p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	// �}�e���A�������̏�Ԃɖ߂�
	pDevice->SetMaterial(&matDef);

	//�X�e���V���Q�ƒl"1"�ɂ���
	pDevice->SetRenderState(D3DRS_STENCILREF,2);
	
	///////////////////////////////////////////////////////////////////
	// �X�e���V���ݒ�3
	///////////////////////////////////////////////////////////////////
	
	//�X�e���V���Q�ƒl�Ɠ��l�ō��i
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);
	//�X�e���V���e�X�g���i�AZ�e�X�g���i�̏ꍇ�X�V���Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);
	//�X�e���V���e�X�g���i�AZ�e�X�g�s���i�̏ꍇ�X�V���Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);
	//�X�e���V���e�X�g�s���i�̏ꍇ�X�V���Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);
	//�J���[�o�b�t�@�ւ̏������݂�L����
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_ALPHA);
	
	//��ʃT�C�Y��2D�������|���S����`��(CSCENE2D���g���Ă͂����Ȃ�)
		
	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v�����~�e�B�u�̎��
									0,//�`�悷��v���~�e�B�u��
									2);
	
	//Z�o�b�t�@�ւ̏������݂�L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	//�X�e���V���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Create�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shadow* Shadow::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel,int nPriority)
{
	Shadow *pRet = new Shadow(nPriority);
	pRet->Init(pos,rot,scl,pTexture,pModel);
	return pRet;
}