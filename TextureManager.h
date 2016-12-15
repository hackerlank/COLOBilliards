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

	int Load(const char *TextureFileName); //ä«óùî‘çÜÇï‘Ç∑ÅAì«ÇﬂÇ»ÇØÇÍÇŒ-1Çï‘Ç∑
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