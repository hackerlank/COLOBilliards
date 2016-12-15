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
// �}�N����`
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Camera *Renderer::m_pCamera=NULL;
Light *Renderer::m_pLight=NULL;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �f�X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Init�֐�
//	:�f�o�C�X�̍쐬
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Renderer::Init(HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}
	
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp,sizeof(d3dpp));	//d3dpp�̒��g��S��0��

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;	//�J���[���[�h�̎w��
	d3dpp.BackBufferCount = 1;	//�o�b�t�@��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;	//�E�B���h�E���[�h/�t���X�N���[�����[�h
	d3dpp.EnableAutoDepthStencil = TRUE; //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //�f�v�X�o�b�t�@�Ƃ���16�r�b�g���g�p
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; //�f�v�X�o�b�t�@�Ƃ���24�r�b�g�A�X�e���V���o�b�t�@�Ƃ���8�r�b�g���g�p

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

	//�f�o�C�X�I�u�W�F�N�g�̐���
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

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice -> SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW /* ���ʂ�������悤�� */);	//�J�����O�̐ݒ�
	m_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); //���u�����h�̐ݒ�
	m_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	
	//���C���[�t���[���\��
	//m_pD3DDevice -> SetRenderState(D3DRS_FILLMODE, 2);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
	//m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_ANISOTROPIC);	//�A�j�\�g���s�b�N�t�B���^
	//m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_ANISOTROPIC);	//�����ɋ߂��Ȃ�ق��Y��ɕ`��ł���
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	m_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	m_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	m_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	m_pCamera = new Camera;
	m_pLight = new Light;

	m_pCamera->Init();
	m_pLight->SetLight();

	////////////////////////////////////////////////////////////////////
	//�����_�[�^�[�Q�b�g
	////////////////////////////////////////////////////////////////////
	
	//�o�b�N�o�b�t�@�̃T�[�t�F�X���擾�ۑ����Ă���
	m_pD3DDevice->GetRenderTarget(0,&m_surfaceBackbff);
	m_pD3DDevice->GetDepthStencilSurface(&m_surfaceDepthbff);

	//�����_�[�^�[�Q�b�g�p�e�N�X�`���A�T�[�t�F�X�̍쐬
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
//	Uninit�֐�
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
//	Update�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Renderer::Update(void)
{
	m_pCamera->Update();
	Scene::UpdateAll();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Draw�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Renderer::Draw(void)
{
	//��ʂ̃N���A
	//m_pD3DDevice -> Clear(0,NULL,(D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);
	m_pD3DDevice -> Clear(0,NULL,(D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);

	//BiginScene
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//�J�����̕`��
		m_pCamera->Draw();
		
		Scene::DrawAll();
		
		//EndScene
		m_pD3DDevice->EndScene();	//�`��̏I��
	}

	//�v���[���g
	m_pD3DDevice -> Present(NULL,NULL,NULL,NULL); //�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GetViewCamera�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3DXMATRIX Renderer::GetViewCamera(void)
{
	return m_pCamera->GetView();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GetRotCamera�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 Renderer::GetRotCamera(void)
{
	return m_pCamera->GetRotCamera();
}