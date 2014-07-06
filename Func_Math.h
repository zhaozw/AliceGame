#ifndef FUNC_MATH_H
#define FUNC_MATH_H

#include <math.h>
#include <DxLib.h>

#define GET_RAND(p) GetRand(p)
// 0�`255�͈̔͂Ɏ��߂�
#define PARAM(p) max(0, min(255, p))

// ����p�x�̒P�ʃx�N�g����x���������B
// ���̎����ɂ���Ēl���قȂ�B
inline float rad2x(float rad);

// ����p�x�̒P�ʃx�N�g����y���������B
// ���̎����ɂ���Ēl���قȂ�B
inline float rad2y(float rad);

// (x1, y1)���猩��(y1, y2)�̊p�x��Ԃ��B
// ���̎����ɂ���Ēl���قȂ�B
float getRad(float x1, float y1, float x2, float y2);

// �x�N�g��(x, y)�̊p�x��Ԃ��B
// ���̎����ɂ���Ēl���قȂ�B
float getRad2(float x, float y);

// DrawRotaGraph�Ői�s�����ɉ摜����]���������Ƃ���
// �w�肷�ׂ��p�x���擾����B
float getGraphAngle(float vx, float vy);

// (x1, y1)��(x2, y2)�̋�����Ԃ��B
float getLong(float x1, float y1, float x2, float y2);
// �x�N�g��(x, y)�̒�����Ԃ��B
float getLong2(float x1, float y1);

float Rand(int bias=0);		//-1�`1�̗���
							// bias��0�ȏ�́A�t���[�����ɑ�����l���g�����Ƃ�
							// ������x-1�`1���ϓ��ɏo��悤�ɂ��邱�Ƃ��o����B
float Rand2(); // 0�`1�̗����B
float Rand_Narrow(int bias=0); // -1�`1�̗����B��Βl�̏������l���o�₷���B
float Rand_Narrow2(int bias=0); // -1�`1�̗����B��Βl�̏������l������ɏo�₷���B
float Rand_Wide(int bias=0); // -1�`1�̗����B��Βl�̑傫���l���o�₷���B
// GetRand�ŏo���ϐ��̒l���Ď��ł���悤�ɂ������́B
int MyGetRand(int randMax);
float deg2rad(float d);
float rad2deg(float r);

// x, y���x�N�g���Ƃ��A������w�肵���p�x�i���W�A���j������]������B
void Rotate(float* x, float* y, const float rad);
// x, y���x�N�g���Ƃ��A�����1�b�Ɏw�肵���p�x�i�x�j����
// ��]����悤�ɉ�]������B
void Rotate(float* x, float* y, const float deg, const int fps);
// x, y���x�N�g���Ƃ��A���K������B
void Normalize(float* x, float* y);

// ���̐����܂�int�lp���A
// cycle�Ŋ��������܂��Ԃ��B
int const SeamLess(int const p, int const cycle);

// ��]�^������Ƃ��A�p���x�i1�b������̉�]�p�x�i�x�j�jdeg,
// ���aradius�ŉ��ꍇ�̑����i1�t���[��������j��Ԃ��B
float GetRotateSpeed(const float deg, const float radius, const int fps);

// ��]�^�����鎞�A���xspeed�A���aradius�ŉ��ꍇ�̊p���x
// �i1�b������̉�]�p�x�i�x�j�j��Ԃ��B
float GetRotateAngleRate(const float speed, const float radius, const int fps);
float GetRotateAngleRate2(const float speed, const float radius, const bool isRadian);

// x��cmp�̐�Βl�̑傫������Ԃ��B
// �������Acmp�̕����傫���ꍇ�Acmp�̕�����x�Ɠ����ɂ���B
float amax(float x, float cmp);
// ��Βl�̏���������Ԃ�
// �������Acmp�̕����������ꍇ�Acmp�̕�����x�Ɠ����ɂ���B
float amin(float x, float cmp);

// 2�̃x�N�g���̂Ȃ��p��Ԃ��B
float GetVecRad(float x1, float y1, float x2, float y2);

// ���W�A���͈̔͂�-M_PI~M_PI�ɐ�������B
float rad2radPI(float rad);

// n-way�e���o�������Ƃ��Ɏg���B
float way2float(int i, int max);

// ���݂̊p�xcnt��_������aim�ɍő��maxRad�����߂Â���B
// �߂�l���C�������p�x�B&cnt�̏ꍇ��cnt�����̂܂ܗ��p����B
float Homing(float cnt, float aim, float maxRad);

#endif // FUNC_MATH_H