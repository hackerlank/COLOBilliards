///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Scene.cpp
// �I�u�W�F�N�g�n�̓����X�[�p�[�N���X
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "Manager.h"
#include "Scene.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �}�N����`
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene *Scene::m_pTop[NUM_PRIORITY]={NULL};
Scene *Scene::m_pCur[NUM_PRIORITY]={NULL};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::Scene(int nPriority):m_nPriority(nPriority)
{
	//�擪���o�^����ĂȂ��ꍇ
	if(m_pTop[nPriority]==NULL)
	{
		m_pTop[nPriority]=this;			//�擪�ɂ��ɂ�������ݒ肷���I�I
	}

	//�I�[���o�^����ĂȂ��ꍇ
	if(m_pCur[nPriority]==NULL)
	{
		m_pCur[nPriority]=this;			//�I�[�ɂ��ɂ�������ݒ肷���I�I
	}
	else
	{
		m_pCur[nPriority]->m_pNext=this;	//���ɂ������̑O�̂��ɂ������̃l�N�X�g�ۊǌɂɂ��ɂ������̃|�C���^�}����I�I
	}

	//�擪��������������
	if(m_pTop[nPriority]==this)
	{
		m_pPrev=NULL;
	}
	else
	{
		m_pPrev=m_pCur[nPriority];			//�O�̂��ɂ������̃|�C���^�����ɂ������̑O�Ƃ��ĕۊǂ����I�I
	}
	m_pDflg=false;
	m_pNext=NULL;
	m_pCur[nPriority]=this;				//�Ō���ɂ��ɂ�������ݒ肷���I�I
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	UpdateAll�֐�
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
		//���S�t���O�������Ă��郂�m������
		for(Scene *pListScene=m_pTop[n]; pListScene!=NULL; pListScene=pScene)
		{
			if(pListScene->m_pDflg==true)
			{
				//���g���擪�̏ꍇ
				if(pListScene == m_pTop[n])
				{
					//�擪�̍������̐l�ɏ���
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

				//���g���Ō���̏ꍇ
				if(pListScene == m_pCur[n])
				{
					//�Ō����O�̐l�ɏ���
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

				//���Ԃ̏ꍇ
				if((pListScene->m_pNext!=NULL)&&(pListScene->m_pPrev!=NULL))
				{
					//�����̑O�ƌ���A������
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
	
	//���
	if(pScene!=NULL)
	{
		pScene->Uninit();
		delete (pScene);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	DrawAll�֐�
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
//	ReleaseAll�֐�
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
					//���g���擪�̏ꍇ
					if(pListScene == m_pTop[n])
					{
						//�擪�̍������̐l�ɏ���
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

					//���g���Ō���̏ꍇ
					if(pListScene == m_pCur[n])
					{
						//�Ō����O�̐l�ɏ���
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

					//���Ԃ̏ꍇ
					if((pListScene->m_pNext!=NULL)&&(pListScene->m_pPrev!=NULL))
					{
						//�����̑O�ƌ���A������
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
			
			//���
			if(pScene!=NULL)
			{
				pScene->Uninit();
				delete (pScene);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Release�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::Release(void)
{
	//���Q���惉���T�[
	m_pDflg=true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ReleasePriority�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Scene::ReleasePriority(int nPriority)
{
	//���C���[���ƍ폜
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