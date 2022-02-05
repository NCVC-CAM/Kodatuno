#include "stdafx.h"
#include "BODY.h"
#include "NURBS_Func.h"
#include "SFQuant.h"

#if defined(_DEBUG) && defined(_MSC_VER)
#define new DEBUG_NEW
#endif

// Function: SFQuant
// コンストラクタ(初期化)
SFQuant::SFQuant()
{
	U = V = 0;
	n = InitCoord();
	E = F = G = 0;
	L = M = N = 0;
}

// Function: SFQuant
// コンストラクタ(基本量を得る)
//
// Parameters:
// *S - NURBS曲面へのポインタ
// u,v - (u, v)パラメータ
SFQuant::SFQuant(NURBSS *S,double u,double v)
{
//	NURBS_Func nf;
	U = u;
	V = v;
//	Coord du = nf.CalcDiffuNurbsS(S,u,v);			// u方向1階微分
//	Coord dv = nf.CalcDiffvNurbsS(S,u,v);			// v方向1階微分
//	Coord duu = nf.CalcDiffNNurbsS(S,2,0,u,v);		// u方向2階微分
//	Coord dvv = nf.CalcDiffNNurbsS(S,0,2,u,v);		// v方向2階微分
//	Coord duv = nf.CalcDiffNNurbsS(S,1,1,u,v);		// u,v方向各1階微分
//	n = nf.CalcNormVecOnNurbsS(S,u,v);				// 法線ベクトル
	Coord du = S->CalcDiffuNurbsS(u,v);			// u方向1階微分
	Coord dv = S->CalcDiffvNurbsS(u,v);			// v方向1階微分
	Coord duu = S->CalcDiffNNurbsS(2,0,u,v);		// u方向2階微分
	Coord dvv = S->CalcDiffNNurbsS(0,2,u,v);		// v方向2階微分
	Coord duv = S->CalcDiffNNurbsS(1,1,u,v);		// u,v方向各1階微分
	n = S->CalcNormVecOnNurbsS(u,v);				// 法線ベクトル
	E = CalcInnerProduct(du,du);				// 第1基本量
	F = CalcInnerProduct(du,dv);				// 第1基本量
	G = CalcInnerProduct(dv,dv);				// 第1基本量
	L = CalcInnerProduct(duu,n);				// 第2基本量
	M = CalcInnerProduct(duv,n);				// 第2基本量
	N = CalcInnerProduct(dvv,n);				// 第2基本量

}

// Function: SetSFQ
// 基本量を得る
//
// Parameters:
// *S - NURBS曲面へのポインタ
// u,v - (u, v)パラメータ
int SFQuant::SetSFQ(NURBSS *S,double u,double v)
{	
//	NURBS_Func nf;
	U = u;
	V = v;
//	Coord du = nf.CalcDiffuNurbsS(S,u,v);			// u方向1階微分
//	Coord dv = nf.CalcDiffvNurbsS(S,u,v);			// v方向1階微分
//	Coord duu = nf.CalcDiffNNurbsS(S,2,0,u,v);		// u方向2階微分
//	Coord dvv = nf.CalcDiffNNurbsS(S,0,2,u,v);		// v方向2階微分
//	Coord duv = nf.CalcDiffNNurbsS(S,1,1,u,v);		// u,v方向各1階微分
//	n = nf.CalcNormVecOnNurbsS(S,u,v);				// 法線ベクトル
	Coord du = S->CalcDiffuNurbsS(u,v);			// u方向1階微分
	Coord dv = S->CalcDiffvNurbsS(u,v);			// v方向1階微分
	Coord duu = S->CalcDiffNNurbsS(2,0,u,v);		// u方向2階微分
	Coord dvv = S->CalcDiffNNurbsS(0,2,u,v);		// v方向2階微分
	Coord duv = S->CalcDiffNNurbsS(1,1,u,v);		// u,v方向各1階微分
	n = S->CalcNormVecOnNurbsS(u,v);				// 法線ベクトル
	E = CalcInnerProduct(du,du);				// 第1基本量
	F = CalcInnerProduct(du,dv);				// 第1基本量
	G = CalcInnerProduct(dv,dv);				// 第1基本量
	L = CalcInnerProduct(duu,n);				// 第2基本量
	M = CalcInnerProduct(duv,n);				// 第2基本量
	N = CalcInnerProduct(dvv,n);				// 第2基本量

	return KOD_TRUE;
}

// Function: CalcMeanCurvature
// NURBS曲面上の(u,v)における平均曲率を求める（オーバーロード）
// 
// Parameters:
// q - 曲面の基本量をセットにした構造体
//
// Retrurn:
// 計算結果
double SFQuant::CalcMeanCurvature(void)
{
	return -(G*L+E*N-2*F*M)/(E*G-F*F)/2;		// 平均曲率
}

// Function: CalcGaussCurvature
// NURBS曲面上の(u,v)におけるガウス曲率を求める（オーバーロード）
//
// Parameters:
// q - 曲面の基本量をセットにした構造体
//
// Retrurn:
// 計算結果
double SFQuant::CalcGaussCurvature(void)
{
	return (L*N-M*M)/(E*G-F*F);					// ガウス曲率
}
