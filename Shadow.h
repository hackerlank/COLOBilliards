#pragma once
#ifndef _Shadow_H_
#define _Shadow_H_

#include "Scene.h"

class Shadow:public Scene
{
public:
	Shadow(int nPriority=1);
	~Shadow();
	
	static Shadow* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel,int nPriority=1);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void TimeLeap(void){};

	//�ʒu���̃Z�b�g&�Q�b�g
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	
	//�p�x���̃Z�b�g&�Q�b�g
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//���݂̏�Ԃ̃Z�b�g
	void SetType(int nType){};
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;	//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD m_numMat;	//�}�e���A���̐�

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���N�X

	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_scl; //�傫��
	int moveflg3D;
	
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	VERTEX_2D *m_aVertex; //���_���
};
#endif