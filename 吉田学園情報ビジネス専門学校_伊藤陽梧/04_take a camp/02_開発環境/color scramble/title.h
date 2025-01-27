//=============================================================================
//
// titleヘッダ [title.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "map.h"

//=============================
// 前方宣言
//=============================
class CPolygon;
class CMapManager;
class CButton_Title;
//*****************************
//クラス定義
//*****************************

//タイトルクラス
class CTitle : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CTitle();
	~CTitle();

	static CTitle *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	//============
	// メンバ変数
	//============
	CPolygon *m_pPolygon;					// ポリゴン
	static CMap *m_pMap;					// ステージのポインタ
	static CMapManager::MAP_TYPE m_MapType;	// マップのタイプ
	static CButton_Title *m_pButton;		// ボタンのポインタ
};

#endif