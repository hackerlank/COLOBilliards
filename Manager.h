#pragma once
#ifndef _Manager_H_
#define _Manager_H_

class Renderer;
class TextureManager;
class InputKeyboard;

class Manager
{
private:
	static InputKeyboard *m_pInputKeyboard;
	static Renderer *m_pRenderer;
	static float num;
public:
	Manager();
	~Manager();

	static void Init(HINSTANCE hInstance,
			HWND hWnd,
			BOOL bWindow);
	static void Uninit(void);
	static void Update(HWND hWnd);
	static void Draw(void);
	static Renderer *GetRenderer(void);
	static LPDIRECT3DTEXTURE9 GetTexture(int TexNum);
	static TextureManager *m_pTextureManager;
};
#endif