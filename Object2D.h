#pragma once
#ifndef _Object2D_H_
#define _Object2D_H_

#include "Scene.h"

class Object2D:public Scene
{
public:
	Object2D(int nPriority=9);
	~Object2D();
	
	static Object2D* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,LPDIRECT3DTEXTURE9 pTexture,int nPriority=9);
	static Object2D* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,int alpha,LPDIRECT3DTEXTURE9 pTexture,int nPriority=9);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size,LPDIRECT3DTEXTURE9 pTexture);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size,int alpha,LPDIRECT3DTEXTURE9 pTexture);
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

	//�g����̃Z�b�g���Q�b�g
	void SetScale(float x,float y,float z);
	void SetScale(D3DXVECTOR3 scl);
	D3DXVECTOR3 GetScale(void){return m_scl;};

	//���݂̏�Ԃ̃Z�b�g
	void SetType(int nType){};
	void SetAnimation(int num);
	void SetAlpha(int alpha);
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scl;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	VERTEX_2D *m_aVertex; //���_���
	
	D3DXVECTOR3 m_posStart; //�����ʒu
	D3DXVECTOR3 m_rotStart; //��������
	D3DXVECTOR3 m_sclStart; //�����傫��
};
#endif