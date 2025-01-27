#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"
//オブジェクトクラス
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_SKYBOX,
		OBJTYPE_PLAYER,
		OBJTYPE_BOX,
		OBJTYPE_ITEM,
		OBJTYPE_FENCE,
		OBJTYPE_CIRCLE,
		OBJTYPE_ENEMY,
		OBJTYPE_GATE,
		OBJTYPE_BULLET,
		OBJTYPE_SCORE,
		OBJTYPE_NUMBER,
		OBJTYPE_PARTICLE,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 2);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	//純粋仮想関数
	virtual HRESULT Init(void)=0;	//初期化処理
	virtual void Uninit(void)=0;	//終了処理
	virtual void Update(void)=0;	//更新処理
	virtual void Draw(void)=0;		//描画処理

	static void UpdateAll(void);	//更新まとめ
	static void DrawAll(void);		//描画まとめ
	static void ReleaseAll(void);	//終了まとめ
	static void DesignationReleaseAll(OBJTYPE type);
	static void SetUpdateStop(bool bUpdateStop);

	static bool GetUpdateStop(void) { return m_bUpdateStop; }

protected:	
	void Release(void);

private:
	OBJTYPE m_objType;					//オブジェクトの種類
	static CScene *m_pTop[OBJTYPE_MAX];	//先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];	//現在のオブジェクトへのポインタ
	CScene *m_pPrev;					//前のオブジェクトへのポインタ
	CScene *m_pNext;					//次のオブジェクトへのポインタ
	static int m_nNumAll;
	int m_nPriority;
	int m_nID;
	static int	m_nCount;
	static int m_nNext;
	static bool m_bRelease;
	bool m_bDeath;
	static bool m_bUpdateStop;
};

#endif // !_RENDERER_H_