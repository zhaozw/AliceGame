// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���Z�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXMATH_H__
#define __DXMATH_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern VECTOR	Get_Triangle_Point_MinPosition( VECTOR Point, VECTOR TrianglePos1, VECTOR TrianglePos2, VECTOR TrianglePos3 ) ;			// �_�Ɉ�ԋ߂��O�p�`��̍��W�𓾂�
extern VECTOR	Get_Line_Point_MinPosition( VECTOR Point, VECTOR LinePos1, VECTOR LinePos2 ) ;											// �_�Ɉ�ԋ߂�����̍��W�𓾂�
extern int		Get_TwoPlane_Line( VECTOR Normal1, float Dist1, VECTOR Normal2, float Dist2, VECTOR *OutDir, VECTOR *OutPos ) ;			// ��̕��ʂ�����������𓾂�( �߂�l�� -1 �̏ꍇ�́A��̖ʂ͕��s )
extern int		Get_TwoLine_MinLength_Rate( VECTOR Direction1, VECTOR Position1, float *OutRate1, VECTOR Direction2, VECTOR Position2, float *OutRate2 ) ;		// ��̐��̍ŋߓ_�̂��ꂼ��̕����x�N�g���̊g��l�𓾂�

extern void		CreateNormalizePlane( FLOAT4 *Plane, VECTOR *Position, VECTOR *Normal ) ;												// ���ʏ�̓_�ƕ��ʂ̖@�����琳�K�����ꂽ���ʃp�����[�^���Z�o����
extern void		SetMathScreenSize( int SizeX, int SizeY ) ;																				// DxMath.cpp �Ŏg�p�����ʂ̃T�C�Y��ݒ肷��

}

#endif // __DXMATH_H__
