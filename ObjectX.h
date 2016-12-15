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

	//位置情報のセット&ゲット
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	
	//角度情報のセット&ゲット
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//現在の状態のセット
	void SetType(int nType){};
private:
	
	Shadow *m_pShadow;

	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;	//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報へのポインタ
	DWORD m_numMat;	//マテリアルの数

	D3DXMATRIX m_mtxWorld;		//ワールドマトリクス

	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_scl; //大きさ

	
	D3DXVECTOR3 m_posStart; //初期位置
	D3DXVECTOR3 m_rotStart; //初期向き
	D3DXVECTOR3 m_sclStart; //初期大きさ

	int moveflg3D;
};
#endif