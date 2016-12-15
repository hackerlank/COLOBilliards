#pragma once
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_


class TextureManager
{
public:
	TextureManager(){};
	~TextureManager(){};
	
	void Init(int nMax);
	void Uninit(void);

	int Load(const char *TextureFileName); //�Ǘ��ԍ���Ԃ��A�ǂ߂Ȃ����-1��Ԃ�
	LPDIRECT3DTEXTURE9 GetTexture(int nId);

private:
	int m_nTextureMax;
	int m_nTextureCount;

	struct TextureData{
		LPDIRECT3DTEXTURE9 pTexture;
		static const int TEXTURE_FILENAME_MAX = 256;
		char fileName[TEXTURE_FILENAME_MAX];
	};

	TextureData *m_pTextureData;
};
#endif