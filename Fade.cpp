///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fade.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "fade.h"
#include "InputKeyboard.h"
#include "Manager.h"
#include <time.h>
#include <windows.h>


#define CLASS_NAME "test"												//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "test"												//�E�B���h�E�̖��O
#define TOP (4)															//���_��

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;
VERTEX_2D g_aVertexFade[TOP]; //���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;

FADE g_fade = FADE_IN;
D3DXCOLOR g_colorFade;//�t�F�[�h�F
float g_nA=1.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̏���������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice=Manager::GetRenderer()->GetDevice();

	g_colorFade = D3DXCOLOR(0,0,0,1.0f);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*TOP,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffFade,
									NULL);
	VERTEX_2D *pVtx;

	g_pVtxBuffFade->Lock(0,0,(void**)&pVtx,0);
		//���W
		pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
	
		//�F���
		pVtx[0].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		pVtx[1].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		pVtx[2].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		pVtx[3].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		
		pVtx[0].tex = D3DXVECTOR2(0.0f/* ���WU */,0.0f /* ���WV */ );
		pVtx[1].tex = D3DXVECTOR2(1.0f/* ���WU */,0.0f /* ���WV */ );
		pVtx[2].tex = D3DXVECTOR2(0.0f/* ���WU */,1.0f /* ���WV */ );
		pVtx[3].tex = D3DXVECTOR2(1.0f/* ���WU */,1.0f /* ���WV */ );
		
		g_pVtxBuffFade->Unlock();

		//�e�N�X�`���̓ǂݍ���
		/*
		D3DXCreateTextureFromFile(pDevice,
									"data\\TEXTURE\\Fade000.jpg",									//�t�@�C���p�X
									&g_pTextureFade);
		*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̏I������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UninitFade(void)
{
	if(g_pTextureFade != NULL)
	{
		g_pTextureFade -> Release();
		g_pTextureFade = NULL;
	}
	
	if(g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̍X�V����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateFade(void)
{
	VERTEX_2D *pVtx;
	if(g_fade != FADE_NONE)
	{	
		//�t�F�[�h�C��
		if(g_fade==FADE_IN)
		{	
			g_nA-=0.01f;

			if(InputKeyboard::GetKeyboardTrigger(DIK_RETURN)==true)
			{
				g_nA=0;
			}

			g_pVtxBuffFade->Lock(0,0,(void**)&pVtx,0);
		
			g_colorFade=D3DXCOLOR(0,0,0,g_nA);
		
			//�F���
			pVtx[0].col = g_colorFade;
			pVtx[1].col = g_colorFade;
			pVtx[2].col = g_colorFade;
			pVtx[3].col = g_colorFade;

			g_pVtxBuffFade->Unlock();

			//�t�F�[�h�I��
			if(g_nA<=0)
			{
				g_fade=FADE_NONE;

			}
		}

		//�t�F�[�h�A�E�g
		if(g_fade==FADE_OUT)
		{
			g_nA+=0.02f;

			if(InputKeyboard::GetKeyboardTrigger(DIK_RETURN)==true)
			{
				g_nA=1.0f;
			}

			g_pVtxBuffFade->Lock(0,0,(void**)&pVtx,0);
		
			g_colorFade=D3DXCOLOR(0,0,0,g_nA);
		
			//�F���
			pVtx[0].col = g_colorFade;
			pVtx[1].col = g_colorFade;
			pVtx[2].col = g_colorFade;
			pVtx[3].col = g_colorFade;

			g_pVtxBuffFade->Unlock();

			//�t�F�[�h�I��
			if(g_nA>1.0f)
			{
				switch(GetMode())
				{
				case MODE_TITLE:
					SetMode(MODE_GAME);
					break;

				case MODE_GAME:
					SetMode(MODE_TITLE);
					break;

				}
				g_fade=FADE_IN;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̕`�揈��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawFade(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;
	pDevice=Manager::GetRenderer()->GetDevice();
	
	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0,g_pVtxBuffFade,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v�����~�e�B�u�̎��
									0,//�`�悷��v���~�e�B�u��
									2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �t�F�[�h�̃Z�b�g����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetFade(FADE fade)
{
	if(fade==FADE_IN)
	{
		g_nA=1.0f;
	}
	
	if(fade==FADE_OUT)
	{
		g_nA=0;
	}

	g_fade=fade;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �t�F�[�h�̌��݂̃��[�h���擾
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FADE GetFade()
{
	return g_fade;
}