#ifndef GAME_BGEFFECT_H
#define GAME_BGEFFECT_H

#include <Windows.h>
#include <DxLib.h>
#include <vector>
#include <array>

// typeID�̗񋓁B
#define GAME_BG_TYPE_NONE				0	// �w�i�Ȃ��B�����`�悵�Ȃ��B
#define GAME_BG_TYPE_DUMMY				1	// �_�~�[�w�i�B�`�F�b�N�摜����ׂĕ\���B

//================================================
// Game_BGEffect�N���X
// 
// �G�t�F�N�g�̂��������w�i�̃N���X�B
// �퓬��ʂ̔w�i�A�}�b�v��ʂ̔w�i�Ȃǂŗ��p����B
// 
namespace BackGroundEffect{
    class Object{
        // �e�N�X�`���֌W
        int texture;
        float texW, texH;
        float uMax, vMax;
        float addU; // UV�A�j���[�V�����p
        float addV; // UV�A�j���[�V�����p

        // ���_�֌W
        //DrawPrimitive2D();
        VERTEX2D* vertex;
        int vertexNum;
        int divNum;
        float polyW, polyH;

        // ���_�C���f�b�N�X
        USHORT* index;
        int indexNum;

        // �p�����
        VECTOR centerPos;
        float rot;
        float scale;


        // Update���̓���t���O�ƃp�����[�^
        float rotateRate; // 1�t���[����rotateRate����������
        float scaleRate; // 1�t���[����scaleRate����������
        float uRate; // 1�t���[����uRate��U�𓮂���
        float vRate; // 1�t���[����vRate��V�𓮂���


        void SetVertexPosition();
        void SetUV();
        
        void SetRotate();
        void SetScale();

        void CreateVertex(int div);
        void CreateIndex();

        bool isDuplicateTexture;

    public:
        Object();
        Object(int graphHandle, int div = 1);
        ~Object();

        void SetGraph(int handle); // �g�p����摜�n���h�����Z�b�g����
        void SetDuplicateGraph(int handle); // �n���h���̃R�s�[��texture�Ƃ��Ďg�p����

        void SetScale(float scale){ this->scale = scale; } // �X�P�[�����Z�b�g

        void SetDivision(int div){ divNum = div; } // �|���S�����������Z�b�g����
        void CreatePolygon(){  // �|���S�����쐬����
            CreateVertex(divNum);
            CreateIndex();
            SetVertexPosition();
            SetTexelUV();
        }
        void SetPolySize(int w,int h); // �|���S���̃T�C�Y�����߂�
        void SetTexelUV(); // �e�N�X�`���ɍ��킹��UV
        void SetPixelUV(); // �|���S���ɍ��킹��UV
        void SetPolarConversionUV(int x, int y); // �ɍ��W�ϊ�

        void SetPosition(int x, int y){ // ���S���W�̐ݒ�
            centerPos.x = (float)x;
            centerPos.y = (float)y;
        };

        // �e�퓮��̃p�����[�^�Z�b�^�[
        void SetRotateRate(float rate){ rotateRate = rate; }
        void SetScaleRate(float rate){ scaleRate = rate; }
        void SetUVRate(float u, float v){ uRate = u; vRate = v; }
        
        void Draw();
        void Update();
    };
}

class Game_BGEffect{
private:
	// �w�i�̃^�C�vID�B
	WORD		typeID;

	// �����^�C�vID���g�p���Ȃ���w�i������ɕω������������̔ėp�p�����[�^�B
	// �g������typeID�ɂ���ĈقȂ�B
	int			param;

	// ���Ԃ̃p�����[�^�B
	// SetTypeID���s���ۂ�0�ɂȂ�AUpdate���Ăяo�����x�ɑ�����B
	// �g�����ǂ����E�g������typeID�ɂ���ĈقȂ�B
	// ����G�t�F�N�g�̊���Ԃ�ς������ꍇ�́A
	// SetRandTime�֐������s����ƓK���Ȓl��time�ɑ�������B
	int			time;

	// �ό`�̊�Ɏg�����W�B
	// ������ėp�I�Ȃ��̂ł���A�g������typeID�ɂ���ĈقȂ�B
	// SetPosition�֐��Ŏw�肷��B
	float		posX;
	float		posY;

	// �J��Ԃ��Ɏg�p����l�ŁA
	// �摜�̕��ƍ����ȂǂɎg�p����B
	// �g������typeID�ɂ���ĈقȂ��Ă��悢�B
	float		loopWidth;
	float		loopHeight;

    
    BackGroundEffect::Object* obj;

public:

	// �R���X�g���N�^
	Game_BGEffect();

	// �^�C�vID��ύX����B
	// �^�C�vID���Ƃ̏������������܂ށB
	bool SetTypeID(WORD id);

	// �^�C�vID���擾����B
	WORD GetTypeID(){ return typeID; };

	// �p�����[�^��ύX����B
	void SetParam(int p){ param = p; };

	// �p�����[�^���擾����B
	int GetParam(){ return param; };

	// �^�C�vID�ƃp�����[�^���܂Ƃ߂ăZ�b�g����B
	bool SetTypeID(WORD id, int param){ SetParam(param); return SetTypeID(id); };

	// ���������s���B
	// �^�C�vID���Ƃ̏������͂��̊֐��ł͂Ȃ�SetTypeID���ōs���B
	bool Initialize();

	// �I���������s���B
	bool Terminate();

	// �^�C�vID���Ƃ̉��Z�������s���B
	// ���̃I�u�W�F�N�g��������N���X���疈�t���[�����s�����B
	void Update();

	// �^�C�vID���Ƃ̕`�揈�����s���B
	// ���̃I�u�W�F�N�g��������N���X���疈�t���[�����s�����B
	void Draw() const;

	// �K���Ȏ��Ԃ�������B
	void SetRandTime();

	// ��ʒu��������B
	void SetPosition(float _x, float _y){ posX = _x; posY = _y; };


};



#endif // GAME_BGEFFECT_H