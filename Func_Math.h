#ifndef FUNC_MATH_H
#define FUNC_MATH_H

#include <math.h>
#include <DxLib.h>

#define GET_RAND(p) GetRand(p)
// 0～255の範囲に収める
#define PARAM(p) max(0, min(255, p))

// ある角度の単位ベクトルのx成分を取る。
// 軸の取り方によって値が異なる。
inline float rad2x(float rad);

// ある角度の単位ベクトルのy成分を取る。
// 軸の取り方によって値が異なる。
inline float rad2y(float rad);

// (x1, y1)から見た(y1, y2)の角度を返す。
// 軸の取り方によって値が異なる。
float getRad(float x1, float y1, float x2, float y2);

// ベクトル(x, y)の角度を返す。
// 軸の取り方によって値が異なる。
float getRad2(float x, float y);

// DrawRotaGraphで進行方向に画像を回転させたいときに
// 指定すべき角度を取得する。
float getGraphAngle(float vx, float vy);

// (x1, y1)と(x2, y2)の距離を返す。
float getLong(float x1, float y1, float x2, float y2);
// ベクトル(x, y)の長さを返す。
float getLong2(float x1, float y1);

float Rand(int bias=0);		//-1～1の乱数
							// biasに0以上の、フレーム毎に増える値を使うことで
							// ある程度-1～1が均等に出るようにすることが出来る。
float Rand2(); // 0～1の乱数。
float Rand_Narrow(int bias=0); // -1～1の乱数。絶対値の小さい値が出やすい。
float Rand_Narrow2(int bias=0); // -1～1の乱数。絶対値の小さい値がさらに出やすい。
float Rand_Wide(int bias=0); // -1～1の乱数。絶対値の大きい値が出やすい。
// GetRandで出た変数の値を監視できるようにしたもの。
int MyGetRand(int randMax);
float deg2rad(float d);
float rad2deg(float r);

// x, yをベクトルとし、それを指定した角度（ラジアン）だけ回転させる。
void Rotate(float* x, float* y, const float rad);
// x, yをベクトルとし、それを1秒に指定した角度（度）だけ
// 回転するように回転させる。
void Rotate(float* x, float* y, const float deg, const int fps);
// x, yをベクトルとし、正規化する。
void Normalize(float* x, float* y);

// 負の数を含むint値pを、
// cycleで割ったあまりを返す。
int const SeamLess(int const p, int const cycle);

// 回転運動するとき、角速度（1秒当たりの回転角度（度））deg,
// 半径radiusで回る場合の速さ（1フレーム当たり）を返す。
float GetRotateSpeed(const float deg, const float radius, const int fps);

// 回転運動する時、速度speed、半径radiusで回る場合の角速度
// （1秒当たりの回転角度（度））を返す。
float GetRotateAngleRate(const float speed, const float radius, const int fps);
float GetRotateAngleRate2(const float speed, const float radius, const bool isRadian);

// xとcmpの絶対値の大きい方を返す。
// ただし、cmpの方が大きい場合、cmpの符号をxと同じにする。
float amax(float x, float cmp);
// 絶対値の小さい方を返す
// ただし、cmpの方が小さい場合、cmpの符号をxと同じにする。
float amin(float x, float cmp);

// 2つのベクトルのなす角を返す。
float GetVecRad(float x1, float y1, float x2, float y2);

// ラジアンの範囲を-M_PI~M_PIに制限する。
float rad2radPI(float rad);

// n-way弾を出したいときに使う。
float way2float(int i, int max);

// 現在の角度cntを狙い方向aimに最大でmaxRadだけ近づける。
// 戻り値が修正した角度。&cntの場合はcntをそのまま利用する。
float Homing(float cnt, float aim, float maxRad);

#endif // FUNC_MATH_H