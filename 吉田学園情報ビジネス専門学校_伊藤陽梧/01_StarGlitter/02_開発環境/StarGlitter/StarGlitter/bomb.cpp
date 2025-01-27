//=============================================================================
//
// ボムの処理 [bomb.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "bomb.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"
#include "bombexplosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_BOMBEXPROSION_POS (D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f))
#define PLAYER2_BOMBEXPROSION_POS (D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f))

#define BOMBEXPROSION_LIFE (76)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBomb::m_pTexture = NULL;

//=============================================================================
// ボムクラスのコンストラクタ
//=============================================================================
CBomb::CBomb() :CScene2D(OBJTYPE_BG)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_BombType = BOMB_TYPE_NONE;
}

//=============================================================================
// ボムクラスのデストラクタ
//=============================================================================
CBomb::~CBomb()
{

}

//=============================================================================
// ボムクラスのテクスチャの読み込み
//=============================================================================
HRESULT CBomb::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOMB, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ボムクラスのテクスチャの破棄
//=============================================================================
void CBomb::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ボムクラスのインスタンス生成
//=============================================================================
CBomb* CBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOMBTTYPE BombType, OBJTYPE objType)
{
	// CBombのポインタ
	CBomb *pBullet = NULL;

	// メモリの確保
	pBullet = new CBomb;

	// pBulletがNULLじゃないとき
	if (pBullet != NULL)
	{
		// ボムのセット
		pBullet->SetBomb(pos, size, BombType, objType);

		// 初期化処理
		pBullet->Init();
	}

	// pBulletを返す
	return pBullet;
}

//=============================================================================
// ボムクラスの初期化処理
//=============================================================================
HRESULT CBomb::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_pTexture);

	return S_OK;
}

//=============================================================================
// ボムクラスの終了処理
//=============================================================================
void CBomb::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// ボムクラスの更新処理
//=============================================================================
void CBomb::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	// 座標と体力の受け取り
	m_pos = GetPosition();

	// 座標を渡す
	SetPosition(m_pos);

	// ボムが使われたとき
	if (m_bUse == true)
	{
		switch (m_BombType)
		{
			// プレイヤー1のボム
		case BOMB_TYPE_PLAYER:
			// ボムの爆発の生成
			CBombexplosion::Create(PLAYER_BOMBEXPROSION_POS, BOMBEXPROSION_LIFE, CBombexplosion::BOMBEXPLOSION_PLAYER, OBJTYPE_EXPLOSION);

			// ボムの終了処理
			Uninit();
			break;

			// プレイヤー2のボム
		case BOMB_TYPE_PLAYER2:
			// ボムの爆発の生成
			CBombexplosion::Create(PLAYER2_BOMBEXPROSION_POS, BOMBEXPROSION_LIFE, CBombexplosion::BOMBEXPLOSION_PLAYER2, OBJTYPE_EXPLOSION);

			// ボムの終了処理
			Uninit();
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// ボムクラスの描画処理
//=============================================================================
void CBomb::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// ボムクラスの使うときの処理
//=============================================================================
void CBomb::UseBomb(void)
{
	// 使う状態にする
	m_bUse = true;
}
