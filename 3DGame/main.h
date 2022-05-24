//=============================================================================
//
// メイン処理 [main.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>						// Windows
#include "d3dx9.h"							// 描画に必要
#define DIRECTINPUT_VERSION (0x0800)		// ビルド時の警告対処用マクロ
#include "dinput.h"							// 入力処理に必要
#include "xaudio2.h"						// XAudio2関連のヘッダー
#include <XInput.h>							// Xinput
#include <vector>	
#include <string>	
#include <map>		
using namespace std;
//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")			// 描画に必要
#pragma comment (lib, "d3dx9.lib")			// [d3dx9, lib]の拡張ライブラリ
#pragma comment (lib, "dxguid.lib")			// DirectXコンポーネント(部品)に必要
#pragma comment (lib, "dinput8.lib")		// DInput入力に必要
#pragma comment (lib, "xinput.lib")			// XInput入力に必要
#pragma comment (lib, "winmm.lib")			// FPS表示処理

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"3DGame"	// ウインドウのキャプション名
#define SCREEN_WIDTH	(1280)				// ウィンドウの幅
#define SCREEN_HEIGHT	(720)				// ウィンドウの高さ	
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)	// ウィンドウの中心幅
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)	// ウィンドウの中心の高さ
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int GetFPS(void);							// FPS取得処理
#endif