#pragma once
#ifndef _ObjectX_H_
#define _ObjectX_H_

#include "Scene.h"
#include "Shadow.h"

class ObjectX:public Scene
{
public:
	ObjectX(int nPriority=3);
	~ObjectX();
	
	static ObjectX* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel,int nPriority=3);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TimeLeap(void);

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
	
	Shadow *m_pShadow;

	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;	//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD m_numMat;	//�}�e���A���̐�

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���N�X

	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_scl; //�傫��

	
	D3DXVECTOR3 m_posStart; //�����ʒu
	D3DXVECTOR3 m_rotStart; //��������
	D3DXVECTOR3 m_sclStart; //�����傫��

	int moveflg3D;
};
#endif