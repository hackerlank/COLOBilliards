#pragma once
#ifndef _Sound_H_
#define _Sound_H_

#include "main.h"

///////////////////////////////////////////////////////////////////////////////
// サウンドファイル
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM
	SOUND_LABEL_TIME,			// 時の巻き戻し
	SOUND_LABEL_EARTH,			// 地響き
	SOUND_LABEL_SE_DAMAGE,		// 衝突
	SOUND_LABEL_SE_MISS,		// 落下
	SOUND_LABEL_MAX,
} SOUND_LABEL;

///////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////
class Sound
{
public:
	Sound(){};
	~Sound(){};
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);

	static void SetVolume(SOUND_LABEL label,float vol);
	
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	static IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// オーディオデータサイズ
};
#endif
