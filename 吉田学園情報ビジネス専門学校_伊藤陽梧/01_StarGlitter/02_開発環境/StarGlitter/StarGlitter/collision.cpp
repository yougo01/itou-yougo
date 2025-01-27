//=============================================================================
//
// 当たり判定の処理 [collision.cpp]
// Author : 伊藤陽梧
//
//=============================================================================
#include "collision.h"
#include "scene2d.h"

//=============================================================================
// 矩形の当たり判定
// pos1   : 当たる側の位置
// size1  : 当たる側のサイズ
// pos2   : 当てられる側の位置
// size2  : 当てられる側のサイズ
// 戻り値 : 当たったかどうかを返す
//=============================================================================
bool CCollision::RectangleCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 size1,
	D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
{
	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y / 2, size1.z / 2) + pos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y / 2, -size1.z / 2) + pos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	// 当たったかどうかを返す
	return bHit;
}

//=============================================================================
// 球の当たり判定
// pos1   : ぶつかる側の位置
// size1  : ぶつかる側のサイズ
// pos2   : ぶつかられる側の位置
// size2  : ぶつかられる側のサイズ
// 戻り値 : ぶつかる側が円の中に入っているかどうか
//=============================================================================
bool CCollision::SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2)
{
	float distance = powf(pos1.x - pos2.x, 2.0f) + powf(pos1.y - pos2.y, 2.0f) + powf(pos1.z - pos2.z, 2.0f); //位置
	float radius = powf(size1 + size2, 2.0f); // 半径

	// 当たったかどうかを返す
	return (distance <= radius);
}

//=============================================================================
// 矩形の当たり判定(シーンのポインタを使う)
// pos    : 当たる側の位置
// size   : 当たる側のサイズ
// pScene : 当てられる側のポインタ
// 戻り値 : 当たったかどうかを返す
//=============================================================================
bool CCollision::PRectangleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 size, CScene *pScene)
{
	D3DXVECTOR3 Getpos = ((CScene2D*)pScene)->GetPosition();
	D3DXVECTOR3 GetSize = ((CScene2D*)pScene)->GetSize();

	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + pos;					//ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + pos;					//ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(GetSize.x / 2, GetSize.y / 2, GetSize.z / 2) + Getpos;	//ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-GetSize.x / 2, -GetSize.y / 2, -GetSize.z / 2) + Getpos; //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x)
	{
		bHit = true;
	}

	// 当たったかどうかを返す
	return bHit;
}