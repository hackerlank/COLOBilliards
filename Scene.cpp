///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Scene.cpp
// オブジェクト系の統括スーパークラス
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "Manager.h"
#include "Scene.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// マクロ定義
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene *Scene::m_pTop[NUM_PRIORITY]={NULL};
Scene *Scene::m_pCur[NUM_PRIORITY]={NULL};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::Scene(int nPriority):m_nPriority(nPriority)
{
	//先頭が登録されてない場合
	if(m_pTop[nPriority]==NULL)
	{
		m_pTop[nPriority]=this;			//先頭におにいちゃんを設定するよ！！
	}

	//終端が登録されてない場合
	if(m_pCur[nPriority]==NULL)
	{
		m_pCur[nPriority]=this;			//終端におにいちゃんを設定するよ！！
	}
	else
	{
		m_pCur[nPriority]->m_pNext=this;	//おにいちゃんの前のおにいちゃんのネクスト保管庫におにいちゃんのポインタ挿れるよ！！
	}

	//先頭が自分だったら
	if(m_pTop[nPriority]==this)
	{
		m_pPrev=NULL;
	}
	else
	{
		m_pPrev=m_pCur[nPriority];			//前のおにいちゃんのポインタをおにいちゃんの前として保管するよ！！
	}
	m_pDflg=false;
	m_pNext=NULL;
	m_pCur[nPriority]=this;				//最後尾におにいちゃんを設定するよ！！
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	UpdateAll関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::UpdateAll(void)
{
	
	Scene *pScene=NULL;
	for(int n=0; n<NUM_PRIORITY; n++)
	{
		for(Scene *pListScene=m_pTop[n]; pListScene!=NULL; pListScene=pScene)
		{
			pScene=pListScene->m_pNext;
			pListScene->Update();
		}
	}
	int a=0;
	int b=0;
	for(int n=0; n<NUM_PRIORITY; n++)
	{
		//死亡フラグが建っているモノを消す
		for(Scene *pListScene=m_pTop[n]; pListScene!=NULL; pListScene=pScene)
		{
			if(pListScene->m_pDflg==true)
			{
				//自身が先頭の場合
				if(pListScene == m_pTop[n])
				{
					//先頭の座を次の人に譲る
					if(pListScene->m_pNext!=NULL)
					{
						m_pTop[n]=pListScene->m_pNext;
						pListScene->m_pNext->m_pPrev=NULL;
					}
					else
					{
						m_pTop[n]=NULL;
					}
				}

				//自身が最後尾の場合
				if(pListScene == m_pCur[n])
				{
					//最後尾を前の人に譲る
					if(pListScene->m_pPrev!=NULL)
					{
						m_pCur[n]=pListScene->m_pPrev;
						pListScene->m_pPrev->m_pNext=NULL;
					}
					else
					{
						m_pCur[n]=NULL;
					}
				}

				//中間の場合
				if((pListScene->m_pNext!=NULL)&&(pListScene->m_pPrev!=NULL))
				{
					//自分の前と後ろを連結する
					pListScene->m_pNext->m_pPrev=pListScene->m_pPrev;
					pListScene->m_pPrev->m_pNext=pListScene->m_pNext;
		
					pListScene->m_pNext=NULL;
					pListScene->m_pPrev=NULL;
				}

				pScene=pListScene->m_pNext;
				pListScene->Uninit();
				delete pListScene;
				pListScene=NULL;
			}
			else
			{
				pScene=pListScene->m_pNext;
			}
		}
	}
	
	//解放
	if(pScene!=NULL)
	{
		pScene->Uninit();
		delete (pScene);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	DrawAll関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::DrawAll(void)
{
	for(int n=0; n<NUM_PRIORITY; n++)
	{
		for(Scene *pListScene=m_pTop[n]; pListScene!=NULL; pListScene=pListScene->m_pNext)
		{
			pListScene->Draw();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ReleaseAll関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::ReleaseAll(void)
{
	for(int n=0; n<NUM_PRIORITY; n++)
	{
		if(m_pTop[n]!=NULL)
		{
			Scene *pScene=NULL;
			for(Scene *pListScene = m_pTop[n]; pListScene != NULL; pListScene = pScene)
			{
				pScene=pListScene->m_pNext;
				pListScene->Uninit();
			}

			for(Scene *pListScene = m_pTop[n]; pListScene != NULL; pListScene = pScene)
			{

				if(pListScene->m_pDflg==true)
				{
					//自身が先頭の場合
					if(pListScene == m_pTop[n])
					{
						//先頭の座を次の人に譲る
						if(pListScene->m_pNext!=NULL)
						{
							m_pTop[n]=pListScene->m_pNext;
							pListScene->m_pNext->m_pPrev=NULL;
						}
						else
						{
							m_pTop[n]=NULL;
						}
					}

					//自身が最後尾の場合
					if(pListScene == m_pCur[n])
					{
						//最後尾を前の人に譲る
						if(pListScene->m_pPrev!=NULL)
						{
							m_pCur[n]=pListScene->m_pPrev;
							pListScene->m_pPrev->m_pNext=NULL;
						}
						else
						{
							m_pCur[n]=NULL;
						}
					}

					//中間の場合
					if((pListScene->m_pNext!=NULL)&&(pListScene->m_pPrev!=NULL))
					{
						//自分の前と後ろを連結する
						pListScene->m_pNext->m_pPrev=pListScene->m_pPrev;
						pListScene->m_pPrev->m_pNext=pListScene->m_pNext;
		
						pListScene->m_pNext=NULL;
						pListScene->m_pPrev=NULL;
					}
					
					pScene=pListScene->m_pNext;
					pListScene->Uninit();
					delete pListScene;
					pListScene=NULL;
				}
			}
			
			//解放
			if(pScene!=NULL)
			{
				pScene->Uninit();
				delete (pScene);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Release関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::Release(void)
{
	//自害せよランサー
	m_pDflg=true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ReleasePriority関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Scene::ReleasePriority(int nPriority)
{
	//レイヤーごと削除
	if (m_pTop[nPriority] == NULL)
	{
		return 0;
	}

	for (Scene * pScene = m_pTop[nPriority]; pScene != NULL; pScene = pScene->m_pNext)
	{
		pScene->m_pDflg = true;
	}

	return -1;
}



Scene* Scene::GetListTop(int nPriority)
{
	return m_pTop[nPriority];
}
	
Scene* Scene::Next(Scene *pScene)
{
	return pScene->m_pNext;
}