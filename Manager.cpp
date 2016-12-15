///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Manager.cpp
// ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "Manager.h"
#include "InputKeyboard.h"
#include "TextureManager.h"
#include "ObjectX.h"
#include "Mesh.h"
#include "Ball.h"
#include "CollisionManager.h"
#include "Cue.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_DATA (12)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureManager *Manager::m_pTextureManager = NULL;
InputKeyboard *Manager::m_pInputKeyboard = NULL;
Renderer *Manager::m_pRenderer = NULL;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Manager::Manager()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// デストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Manager::~Manager()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初期化処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Manager::Init(HINSTANCE hInstance,
			HWND hWnd,
			BOOL bWindow)
{
	//レンダラーの初期化処理
	m_pRenderer = new Renderer;
	m_pRenderer->Init(hWnd,true);

	//キーボードの初期化処理
	m_pInputKeyboard = new InputKeyboard;
	m_pInputKeyboard->Init(hInstance,hWnd);

	//	TexManagerの初期化処理
	m_pTextureManager = new TextureManager;
	m_pTextureManager->Init(MAX_DATA);

	//テクスチャファイルの読み込み
	m_pTextureManager->Load("./data/TEXTURE/WhiteBall.jpg");			// [0]WhiteBall
	m_pTextureManager->Load("./data/TEXTURE/Ball01.jpg");				// [1]Ball01
	m_pTextureManager->Load("./data/TEXTURE/Ball02.jpg");				// [2]Ball02
	m_pTextureManager->Load("./data/TEXTURE/Ball03.jpg");				// [3]Ball03
	m_pTextureManager->Load("./data/TEXTURE/Ball04.jpg");				// [4]Ball04
	m_pTextureManager->Load("./data/TEXTURE/Ball05.jpg");				// [5]Ball05
	m_pTextureManager->Load("./data/TEXTURE/Ball06.jpg");				// [6]Ball06
	m_pTextureManager->Load("./data/TEXTURE/Ball07.jpg");				// [7]Ball07
	m_pTextureManager->Load("./data/TEXTURE/Ball08.jpg");				// [8]Ball08
	m_pTextureManager->Load("./data/TEXTURE/Ball09.jpg");				// [9]Ball09
	m_pTextureManager->Load("./data/TEXTURE/Field.jpg");				// [10]Field
	m_pTextureManager->Load("./data/TEXTURE/Wood.jpg");					// [11]Wood

	// 当たり判定システム
	CollisionManager::Create();

	// ボード
	ObjectX::Create(D3DXVECTOR3(0.0f,-5.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),m_pTextureManager->GetTexture(10),"data\\MODEL\\BilliardBoard.x",1);
	// マット
	//Mesh::Create(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,m_pTextureManager->GetTexture(10),1);

	// 白球
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3( -60.0f, 5.0f,  0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",0),0);

	// 9球
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  40.0f, 5.0f,  0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",1),1);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  50.0f, 5.0f, -5.5f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",5),5);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  50.0f, 5.0f,  5.5f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",6),6);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  60.0f, 5.0f,-11.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",2),2);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  60.0f, 5.0f,  0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",9),9);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  60.0f, 5.0f, 11.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",4),4);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  70.0f, 5.0f, -5.5f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",7),7);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  70.0f, 5.0f,  5.5f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",8),8);
	CollisionManager::AddCollision(Ball::Create(D3DXVECTOR3(  80.0f, 5.0f,  0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),"data\\MODEL\\BilliardsBall.x",3),3);

	// キュー
	Cue::Create(D3DXVECTOR3( -100.0f,  50.0f,  0.0f),D3DXVECTOR3(0,0,0));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 終了処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Manager::Uninit(void)
{
	//終了処理
	//キーボードの終了処理
	if(m_pInputKeyboard!=NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard=NULL;
	}

	if(m_pTextureManager!=NULL)
	{
		m_pTextureManager->Uninit();
		delete m_pTextureManager;
		m_pTextureManager=NULL;
	}

	if(m_pRenderer!=NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer=NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Manager::Update(HWND hWnd)
{
	m_pInputKeyboard->Update(hWnd);
	
	m_pRenderer->Update();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 描画処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Manager::Draw(void)
{
	m_pRenderer->Draw();
}

Renderer *Manager::GetRenderer(void)
{
	return m_pRenderer;
}

LPDIRECT3DTEXTURE9 Manager::GetTexture(int TexNum)
{
	return m_pTextureManager->GetTexture(TexNum);
}