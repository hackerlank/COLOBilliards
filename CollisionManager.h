#pragma once
#ifndef _CollisionManager_H_
#define _CollisionManager_H_

#include "Scene.h"
class Ball;
#define MAX_BALL (10)

class CollisionManager:public Scene
{
public:
	CollisionManager(int nPriority=4);
	~CollisionManager();
	
	static CollisionManager* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Collision(Ball *Obj1,Ball *Obj2);
	void Draw(void);

	static bool AddCollision(Ball *Object,int num);
	static void ReleaseCollision(int num);

	int GetType(void){return OBJ_TYPE;};		//オブジェクトの種類を返す

	//位置情報のセット&ゲット
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	
	//角度情報のセット&ゲット
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//現在の状態のセット
	void SetType(int nType){OBJ_TYPE = nType;};

private:
	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_scl; //大きさ
	static Ball *m_pSceneList[MAX_BALL];
};
#endif