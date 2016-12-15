#pragma once
#ifndef _Mesh_H_
#define _Mesh_H_

#include "Scene.h"
#define GYOU (30)														//�s��
#define RETU (30)														//��
#define SIZE (10.0f)													//Field�̈�̃u���b�N�̑傫��

class Mesh:public Scene
{
public:
	Mesh(int nPriority=3);
	~Mesh();
	
	static Mesh* Create(float Xsize,float Ysize,float Zsize,float Xpos,float Ypos,float Zpos,LPDIRECT3DTEXTURE9 pTexture,int nPriority=3);
	HRESULT Init(float Xsize,float Ysize,float Zsize,float Xpos,float Ypos,float Zpos,LPDIRECT3DTEXTURE9 pTexture);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TimeLeap(void){};

	//�ʒu���̃Z�b�g&�Q�b�g
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	static D3DXVECTOR3 GetPosition(D3DXVECTOR3 pos, int num);
	
	//�p�x���̃Z�b�g&�Q�b�g
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//���݂̏�Ԃ̃Z�b�g
	void SetType(int nType){};

	static bool WaveField(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scl;

	static D3DXVECTOR3 m_Center;

	static bool m_waveflg;
	
	static float m_time;

	float m_waveheight;

	static bool Collapseflg;

	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���N�X
	int moveflg;
	
	int m_INDEX;	//�C���f�N�X��
	int m_TOP;	//���_��

	static float m_aHeightMap[(GYOU+1)*(RETU+1)];	//�����}�b�v
	D3DXVECTOR3* m_pNormalMap;
	
	static VERTEX_3D *pVtx;
};
#endif