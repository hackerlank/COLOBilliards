#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

//メモリリーク検査/////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define D3D_DEBUG_INFO	//textureの中身が見れるように

#include <windows.h>
#include "d3dx9.h"													//描画処理用

//メモリリーク検査関係/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif	//_DEBUG
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"
#include "Renderer.h"
#include <dxerr.h>

//ライブラリのリンク
#pragma comment (lib,"d3d9.lib")									//描画処理用
#pragma comment (lib,"d3dx9.lib")									//上記の拡張ライブラリ
#pragma comment (lib,"dxguid.lib")									//DirectXコンポネート使用に必要
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxerr.lib")									//HRESULTが何を返しているのか分かる

#define SCREEN_WIDTH (1200)											//画面の幅
#define SCREEN_HEIGHT (750)											//画面の高さ

#define MAX_KEYPATTERN (7)

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1/*テクスチャ座標*/)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//上記のフォーマットに合わせた構造体
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;


/* ===== 3Dフォーマットに合わせた構造体 ===== */
typedef struct
{
	D3DXVECTOR3 pos;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線
	D3DCOLOR col;			// 頂点カラー
	D3DXVECTOR2 tex;		// テクスチャ座標
}VERTEX_3D;

typedef enum
{
	MODE_TITLE=0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX,
}MODE;

void SetMode(MODE mode);
MODE GetMode(void); //現在のモードを取得するよ！！

#endif