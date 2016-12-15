#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#define NUM_PRIORITY (11)

class Scene
{
private:
	static Scene *m_pTop[NUM_PRIORITY];				//���X�g�̐擪�|�C���^
	static Scene *m_pCur[NUM_PRIORITY];				//���X�g�̖����|�C���^
	Scene *m_pPrev;									//���g�̑O�ւ̃|�C���^
	Scene *m_pNext;									//���g�̌�ւ̃|�C���^
	bool m_pDflg;										//���S�t���O
	int m_nPriority;
public:
	Scene(int nPriority=0);
	virtual ~Scene(){};

	virtual HRESULT Init(char *FilePass,float Xsize,float Ysize,float Xpos,float Ypos){return 0;};
	virtual void Uninit(void)=0;
	virtual void Update(void)=0;						//Set���ꂽ���𔽉f
	virtual void Draw(void)=0;							//�`��
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static int ReleasePriority(int nPriority);
	void Release(void);
	
	static Scene* GetListTop(int nPriority);			//�w�肳�ꂽ�v���C�I���e�B�̐擪�ɂ���I�u�W�F�N�g�̃|�C���^��Ԃ�
	static Scene* Next(Scene *pScene);				//���X�g���ЂƂ���
	virtual int GetType(void){return OBJ_TYPE;};		//�I�u�W�F�N�g�̎�ނ�Ԃ�

	//�ʒu���̃Z�b�g&�Q�b�g
	virtual void SetPosition(float x,float y,float z)=0;
	virtual void SetPosition(D3DXVECTOR3 pos)=0;
	virtual D3DXVECTOR3 GetPosition(void)=0;
	
	//�p�x���̃Z�b�g&�Q�b�g
	virtual void SetRotation(float x,float y,float z)=0;
	virtual void SetRotation(D3DXVECTOR3 rot)=0;
	virtual D3DXVECTOR3 GetRotation(void)=0;

	//���݂̏�Ԃ̃Z�b�g
	virtual void SetType(int nType){OBJ_TYPE = nType;};
	
	int OBJ_TYPE;										//�I�u�W�F�N�g�̎��(�ǂ⏰�Ȃǂ̋��)
};

#endif