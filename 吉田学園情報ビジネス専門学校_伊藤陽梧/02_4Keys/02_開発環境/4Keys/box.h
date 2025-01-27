//=============================================================================
//
// BOXの処理 [box.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _BOX_H_
#define _BOX_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModel;

//マクロ定義
#define BOX_SIZE 50.0f
//=============================================================================
// プレイヤークラス
//=============================================================================
class CBox :public CScene
{
public:
	CBox(int nPriority = CScene::OBJTYPE_BOX);//コンストラクタ
	~CBox();//デストラクタ

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_NORMAL,//普通
		TYPE_BREAKED,//壊れた
		TYPE_MAX
	}TYPE;
	static CBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type);//生成処理
	static HRESULT Load(void);//モデルの読み込み
	static void Unload(void);//モデルの破棄
	static HRESULT LoadTexture(void);//テクスチャの読み込み
	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	//受け渡し処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }//場所
	D3DXVECTOR3 GetRot(void) { return m_rot; }//角度
	D3DXVECTOR3 GetSize(void) { return m_size; };//サイズ
	bool HitBox(void);
private:
	bool CBox::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2);
	static LPD3DXMESH m_pMesh[TYPE_MAX];	  // メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX]; // マテリアル情報のポインタ
	static DWORD m_nNumMat[TYPE_MAX];	 // マテリアル情報の数
	D3DXMATRIX m_mtxWorld;	     // 行列計算用
	static char* m_apFileName[TYPE_MAX]; // ファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX][50];

	D3DXVECTOR3 m_pos;					// 場所
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 大きさ
	int         m_type;                 //種類
	bool        m_bHit;//ヒットしたか
	CModel *m_pModel; // モデルクラスのポインタ
};

#endif