#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY_PARTS (13) // プレイヤーのモデルのパーツの最大数
#define MAX_MATERIAL (50)
#define MOTION_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/motion.txt") // モーションのテキスト
#define LOAD_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/enemy.txt") // 各モデルパーツの初期値

#define ENEMY_SIZE_X 10.0f//　当たり判定サイズ
#define ENEMY_SIZE_Y 100.0f
#define ENEMY_SIZE_Z 20.0f
//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;
class CModel;
class CScene;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy :public CScene
{
public:
	typedef enum
	{
		ENEMYSTATE_NOMAL = 0,
		ENEMYSTATE_ITEM,
	}ENEMYSTATE;

	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);//コンストラクタ
	~CEnemy();//デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);//生成処理
	static HRESULT Load(void);//モデルの読み込み
	static void Unload(void);//モデルの破棄
	static HRESULT LoadTexture(void);//テクスチャの読み込み

	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void HitBullet(int nDamage,int nType);
	void EnemyCollision(void);

	static void SetChase(bool bChase);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	LPD3DXMESH GetMesh(void) { return m_pMesh[MAX_ENEMY_PARTS]; }
	ENEMYSTATE GetEnemyState(void) { return m_EnemyState; }
	LPD3DXMESH GetEnemyMesh(int nCount) { return m_pMesh[nCount]; }

private:
	static LPD3DXMESH m_pMesh[MAX_ENEMY_PARTS];		 // メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[MAX_ENEMY_PARTS]; // マテリアル情報のポインタ
	static DWORD m_nNumMat[MAX_ENEMY_PARTS];		 // マテリアル情報の数
	static D3DXMATRIX m_mtxWorld[MAX_ENEMY_PARTS];	 // 行列計算用
	static int m_nldxModelParent[MAX_ENEMY_PARTS];	 // 親モデルのインデックス
	static char* m_apFileName[MAX_ENEMY_PARTS];		 // ファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY_PARTS][MAX_MATERIAL];
	static char* m_apTextureFileName[MAX_ENEMY_PARTS];

	D3DXVECTOR3 m_pos;					// 場所
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 大きさ
	D3DXVECTOR3 m_Getpos;				// 受け取った場所
	D3DXVECTOR3 m_Getrot;				// 受け取った角度
	D3DXVECTOR3 m_Getsize;				// 受け取った大きさ
	CMotion *m_pMotion;					// モーションクラスのポインタ
	CModel *m_pModel[MAX_ENEMY_PARTS];	// モデルクラスのポインタ
	static bool m_bChase;				// チェイス判定
	bool m_bHit;						// ダメージを受けている判定
	bool m_bAttack;						// 攻撃判定
	int m_nCntAttack;					// 攻撃速度
	int m_nEnemyLife;					// 敵の体力
	int m_nCntFrame;					// フレームカウント
	int m_nDamageCnt;					// ダメージモーションフレーム
	ENEMYSTATE m_EnemyState;			// 敵の状態

	//レイ用

};

#endif