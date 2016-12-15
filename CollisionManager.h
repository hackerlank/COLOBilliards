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

	int GetType(void){return OBJ_TYPE;};		//�I�u�W�F�N�g�̎�ނ�Ԃ�

	//�ʒu���̃Z�b�g&�Q�b�g
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	
	//�p�x���̃Z�b�g&�Q�b�g
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//���݂̏�Ԃ̃Z�b�g
	void SetType(int nType){OBJ_TYPE = nType;};

private:
	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_scl; //�傫��
	static Ball *m_pSceneList[MAX_BALL];
};
#endif