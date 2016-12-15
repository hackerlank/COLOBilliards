#pragma once
#ifndef _Mesh_H_
#define _Mesh_H_

#include "Scene.h"
#define GYOU (30)														//行数
#define RETU (30)														//列数
#define SIZE (10.0f)													//Fieldの一つのブロックの大きさ

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

	//位置情報のセット&ゲット
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	static D3DXVECTOR3 GetPosition(D3DXVECTOR3 pos, int num);
	
	//角度情報のセット&ゲット
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//現在の状態のセット
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
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデクスバッファへのポインタ
	D3DXMATRIX m_mtxWorld;		//ワールドマトリクス
	int moveflg;
	
	int m_INDEX;	//インデクス数
	int m_TOP;	//頂点数

	static float m_aHeightMap[(GYOU+1)*(RETU+1)];	//高さマップ
	D3DXVECTOR3* m_pNormalMap;
	
	static VERTEX_3D *pVtx;
};
#endif