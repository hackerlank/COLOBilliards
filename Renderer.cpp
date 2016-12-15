///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Renderer.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Manager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// マクロ定義
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Camera *Renderer::m_pCamera=NULL;
Light *Renderer::m_pLight=NULL;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// デストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Init関数
//	:デバイスの作成
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Renderer::Init(HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}
	
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp,sizeof(d3dpp));	//d3dppの中身を全て0に

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;	//カラーモードの指定
	d3dpp.BackBufferCount = 1;	//バッファ数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;	//ウィンドウモード/フルスクリーンモード
	d3dpp.EnableAutoDepthStencil = TRUE; //デプスバッファとステンシルバッファを作成
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //デプスバッファとして16ビットを使用
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; //デプスバッファとして24ビット、ステンシルバッファとして8ビットを使用

	if(bWindow == TRUE)
	{
		d3dpp.FullScreen_RefreshRateInHz = 0; 
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval =D3DPRESENT_INTERVAL_DEFAULT;
	}

	//デバイスオブジェクトの生成
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp,
									&m_pD3DDevice)))
	{
		
		if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&m_pD3DDevice)))
		{
			
			if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	D3DXCreateFont(m_pD3DDevice,18,0,0,0,
					FALSE,SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal",
					&m_pD3DFont);

	//レンダーステートの設定
	m_pD3DDevice -> SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW /* 裏面も見えるように */);	//カリングの設定
	m_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); //αブレンドの設定
	m_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	
	//ワイヤーフレーム表示
	//m_pD3DDevice -> SetRenderState(D3DRS_FILLMODE, 2);

	//サンプラーステートの設定
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
	//m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_ANISOTROPIC);	//アニソトロピックフィルタ
	//m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_ANISOTROPIC);	//水平に近くなるほど綺麗に描画できる
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	//テクスチャステージステートの設定
	m_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	m_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	m_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	m_pCamera = new Camera;
	m_pLight = new Light;

	m_pCamera->Init();
	m_pLight->SetLight();

	////////////////////////////////////////////////////////////////////
	//レンダーターゲット
	////////////////////////////////////////////////////////////////////
	
	//バックバッファのサーフェスを取得保存しておく
	m_pD3DDevice->GetRenderTarget(0,&m_surfaceBackbff);
	m_pD3DDevice->GetDepthStencilSurface(&m_surfaceDepthbff);

	//レンダーターゲット用テクスチャ、サーフェスの作成
	LPDIRECT3DTEXTURE9 texture;
	D3DXCreateTextureFromFile(m_pD3DDevice,
								"./data/TEXTURE/Field.jpg",
								&texture);
	m_pD3DDevice->CreateTexture(SCREEN_WIDTH,SCREEN_HEIGHT,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&texture,NULL);
	texture->GetSurfaceLevel(0,&m_surfaceBackbff2);
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH,SCREEN_HEIGHT,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&m_surfaceDepthbff2,NULL);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Uninit関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Renderer::Uninit(void)
{
	if(m_pD3DFont != NULL)
	{
		m_pD3DFont->Release();
		m_pD3DFont = NULL;
	}

	if(m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	if(m_pD3D != NULL)
	{
		m_pD3D -> Release();
		m_pD3D = NULL;
	}

	m_pCamera->Uninit();
	delete m_pCamera;
	m_pCamera=NULL;

	delete m_pLight;
	m_pLight=NULL;
	
	Scene::ReleaseAll();
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Update関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Renderer::Update(void)
{
	m_pCamera->Update();
	Scene::UpdateAll();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Draw関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Renderer::Draw(void)
{
	//画面のクリア
	//m_pD3DDevice -> Clear(0,NULL,(D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);
	m_pD3DDevice -> Clear(0,NULL,(D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);

	//BiginScene
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//カメラの描画
		m_pCamera->Draw();
		
		Scene::DrawAll();
		
		//EndScene
		m_pD3DDevice->EndScene();	//描画の終了
	}

	//プレゼント
	m_pD3DDevice -> Present(NULL,NULL,NULL,NULL); //フロントバッファとバックバッファの入れ替え
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GetViewCamera関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3DXMATRIX Renderer::GetViewCamera(void)
{
	return m_pCamera->GetView();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GetRotCamera関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 Renderer::GetRotCamera(void)
{
	return m_pCamera->GetRotCamera();
}