///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//メモリリーク検査/////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Sound.h"
#include "SceneGame.h"
#include "Fade.h"
#include <time.h>

#define CLASS_NAME "Billiards"												//ウィンドウクラスの名前
#define WINDOW_NAME "Billiards"												//ウィンドウの名前
#define TOP (4)															//頂点数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND,
						UINT,
						WPARAM,
						LPARAM);
HRESULT Init(HINSTANCE hInstance,
			HWND hWnd,
			BOOL bWindow);
void Uninit(void);
void Update(HWND hWnd);
void Draw(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int g_nCountFPS = 0;
MODE g_mode = MODE_GAME;
HINSTANCE g_hInstance;

HWND hWnd;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	//メモリリーク検査
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	timeBeginPeriod(1);	//分解能を設定
	dwExecLastTime =
	dwFPSLastTime = timeGetTime(); //現在時刻を取得
	dwCurrentTime =
	dwFrameCount = 0;
	
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
				CS_CLASSDC,
				WndProc,
				0,
				0,
				hInstance,
				NULL,
				LoadCursor(NULL,IDC_ARROW),
				(HBRUSH)(COLOR_WINDOW+1),
				NULL,
				CLASS_NAME,
				NULL
	};
	//HWND hWnd;
	MSG msg;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウの生成
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							SCREEN_WIDTH,//幅
							SCREEN_HEIGHT,//高さ
							NULL,
							NULL,
							hInstance,
							NULL);

	//ウィンドウの表示
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
	//初期化
	Sound *pSound = new Sound;
	pSound->Init(hWnd);

	SceneGame::Init(hInstance,hWnd,0);
	
	//フェードの初期化
	InitFade();

	//InitTitle();

	//メッセージループ
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE) != 0)
		{
			if(msg.message == WM_QUIT)
			{
			break;
			}
			else
			{
				//メッセージ翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount*1000)/(dwCurrentTime-dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000/60))
			{
				dwExecLastTime = dwCurrentTime;
				//更新処理
				Update(hWnd);
				//描画処理
				Draw();
				dwFrameCount++;
			}
			timeEndPeriod(1); //分解能を戻す
		}
	}

	//ウィンドウクラス登録解除
	UnregisterClass(CLASS_NAME,wcex.hInstance);

	//終了処理
	//UninitTitle();
	SceneGame::Uninit();
	pSound->Uninit();
	delete pSound;
	
	return (int)msg.wParam;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ウィンドウプロシージャ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd,
						UINT uMsg,
						WPARAM wParam,
						LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY :
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN :
		switch(wParam)
		{

		//Escキーでウィンドウを閉じる
		case VK_ESCAPE :
			DestroyWindow(hWnd);
			break;

		default:
			break;

		}
		break;

	default :
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void Update(HWND hWnd)
{
	//g_pCManage->Update(hWnd);
	switch(g_mode)
	{
	case MODE_TITLE:
		//UpdateTitle();
		break;

	case MODE_GAME:
		SceneGame::Update(hWnd);
		break;
	}
	UpdateFade();
}

void Draw(void)
{
	//g_pCManage->Draw();

	switch(g_mode)
	{
		case MODE_TITLE:
			//DrawTitle();
			break;

		case MODE_GAME:
			SceneGame::Draw();
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// モードをセット！
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetMode(MODE mode)
{
	g_mode = mode;
	switch(g_mode)
	{
	case MODE_TITLE:
		SetFade(FADE_IN);
		//タイトルの初期化処理
		//InitTitle();
		break;

	case MODE_GAME:
		//タイトルの終了処理
		//UninitTitle();

		SetFade(FADE_IN);
		//SceneGame::Init(g_hInstance,hWnd,0);
		break;

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 現在のモードを取得！
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MODE GetMode(void)
{
	return g_mode;
}
