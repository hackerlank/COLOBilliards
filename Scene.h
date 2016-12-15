#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#define NUM_PRIORITY (11)

class Scene
{
private:
	static Scene *m_pTop[NUM_PRIORITY];				//リストの先頭ポインタ
	static Scene *m_pCur[NUM_PRIORITY];				//リストの末尾ポインタ
	Scene *m_pPrev;									//自身の前へのポインタ
	Scene *m_pNext;									//自身の後へのポインタ
	bool m_pDflg;										//死亡フラグ
	int m_nPriority;
public:
	Scene(int nPriority=0);
	virtual ~Scene(){};

	virtual HRESULT Init(char *FilePass,float Xsize,float Ysize,float Xpos,float Ypos){return 0;};
	virtual void Uninit(void)=0;
	virtual void Update(void)=0;						//Setされた情報を反映
	virtual void Draw(void)=0;							//描画
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static int ReleasePriority(int nPriority);
	void Release(void);
	
	static Scene* GetListTop(int nPriority);			//指定されたプライオリティの先頭にあるオブジェクトのポインタを返す
	static Scene* Next(Scene *pScene);				//リストをひとつ次へ
	virtual int GetType(void){return OBJ_TYPE;};		//オブジェクトの種類を返す

	//位置情報のセット&ゲット
	virtual void SetPosition(float x,float y,float z)=0;
	virtual void SetPosition(D3DXVECTOR3 pos)=0;
	virtual D3DXVECTOR3 GetPosition(void)=0;
	
	//角度情報のセット&ゲット
	virtual void SetRotation(float x,float y,float z)=0;
	virtual void SetRotation(D3DXVECTOR3 rot)=0;
	virtual D3DXVECTOR3 GetRotation(void)=0;

	//現在の状態のセット
	virtual void SetType(int nType){OBJ_TYPE = nType;};
	
	int OBJ_TYPE;										//オブジェクトの種類(壁や床などの区別)
};

#endif