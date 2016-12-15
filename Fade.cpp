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


#define CLASS_NAME "test"												//ウィンドウクラスの名前
#define WINDOW_NAME "test"												//ウィンドウの名前
#define TOP (4)															//頂点数

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;
VERTEX_2D g_aVertexFade[TOP]; //頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;

FADE g_fade = FADE_IN;
D3DXCOLOR g_colorFade;//フェード色
float g_nA=1.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの初期化処理
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
		//座標
		pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
	
		//色情報
		pVtx[0].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		pVtx[1].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		pVtx[2].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		pVtx[3].col = g_colorFade;//D3DCOLOR_RGBA(255,255,255,0);
		
		pVtx[0].tex = D3DXVECTOR2(0.0f/* 座標U */,0.0f /* 座標V */ );
		pVtx[1].tex = D3DXVECTOR2(1.0f/* 座標U */,0.0f /* 座標V */ );
		pVtx[2].tex = D3DXVECTOR2(0.0f/* 座標U */,1.0f /* 座標V */ );
		pVtx[3].tex = D3DXVECTOR2(1.0f/* 座標U */,1.0f /* 座標V */ );
		
		g_pVtxBuffFade->Unlock();

		//テクスチャの読み込み
		/*
		D3DXCreateTextureFromFile(pDevice,
									"data\\TEXTURE\\Fade000.jpg",									//ファイルパス
									&g_pTextureFade);
		*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの終了処理
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
// ポリゴンの更新処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateFade(void)
{
	VERTEX_2D *pVtx;
	if(g_fade != FADE_NONE)
	{	
		//フェードイン
		if(g_fade==FADE_IN)
		{	
			g_nA-=0.01f;

			if(InputKeyboard::GetKeyboardTrigger(DIK_RETURN)==true)
			{
				g_nA=0;
			}

			g_pVtxBuffFade->Lock(0,0,(void**)&pVtx,0);
		
			g_colorFade=D3DXCOLOR(0,0,0,g_nA);
		
			//色情報
			pVtx[0].col = g_colorFade;
			pVtx[1].col = g_colorFade;
			pVtx[2].col = g_colorFade;
			pVtx[3].col = g_colorFade;

			g_pVtxBuffFade->Unlock();

			//フェード終了
			if(g_nA<=0)
			{
				g_fade=FADE_NONE;

			}
		}

		//フェードアウト
		if(g_fade==FADE_OUT)
		{
			g_nA+=0.02f;

			if(InputKeyboard::GetKeyboardTrigger(DIK_RETURN)==true)
			{
				g_nA=1.0f;
			}

			g_pVtxBuffFade->Lock(0,0,(void**)&pVtx,0);
		
			g_colorFade=D3DXCOLOR(0,0,0,g_nA);
		
			//色情報
			pVtx[0].col = g_colorFade;
			pVtx[1].col = g_colorFade;
			pVtx[2].col = g_colorFade;
			pVtx[3].col = g_colorFade;

			g_pVtxBuffFade->Unlock();

			//フェード終了
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
// ポリゴンの描画処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawFade(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;
	pDevice=Manager::GetRenderer()->GetDevice();
	
	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0,g_pVtxBuffFade,0,sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureFade);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリンミティブの種類
									0,//描画するプリミティブ数
									2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// フェードのセット処理
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
// フェードの現在のモードを取得
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FADE GetFade()
{
	return g_fade;
}