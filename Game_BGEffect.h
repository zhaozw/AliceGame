#ifndef GAME_BGEFFECT_H
#define GAME_BGEFFECT_H

#include <Windows.h>
#include <DxLib.h>
#include <vector>
#include <array>

// typeID�̗񋓁B
#define GAME_BG_TYPE_NONE				0	// �w�i�Ȃ��B�����`�悵�Ȃ��B
#define GAME_BG_TYPE_DUMMY				1	// �_�~�[�w�i�B�`�F�b�N�摜����ׂĕ\���B
#define GAME_BG_TYPE_LOOP_WAVE          2   // �g�{���s�ړ�
#define GAME_BG_TYPE_HUE                3   // �F���ω�
#define GAME_BG_TYPE_PC                 4   // �ɍ��W�ϊ�

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
        float alpha;
        // �ɍ��W�ϊ��p
        float pcFacter;
        int pcX, pcY;
        bool isPolarConversion;

        // 
        float pcU, pcV;

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
        float sinThetaRate;
        float cosThetaRate;
        float sinWaveTheta;
        float sinWaveFacter;
        float cosWaveTheta;
        float cosWaveFacter;

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

        void SetAlpha(float a){ alpha = a; } // �A���t�@�l��ݒ�

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
        void SetPolarConversionFacter(float facter); // �ɍ��W�ϊ��̌��������v�Z����B�@=r^2*facter
        void SetPolarConversionXY(int x, int y); // �ɍ��W�ϊ��̏ꏊ��ݒ肷��

        void SetPosition(int x, int y){ // ���S���W�̐ݒ�
            centerPos.x = (float)x;
            centerPos.y = (float)y;
        };

        // �e�퓮��̃p�����[�^�Z�b�^�[
        void SetRotateRate(float rate){ rotateRate = rate; }
        void SetScaleRate(float rate){ scaleRate = rate; }
        void SetUVRate(float u, float v){ uRate = u; vRate = v; }
        void SetSinThetaRate(float rad){
            sinThetaRate = rad;
        }
        void SetCosThetaRate(float rad){
            cosThetaRate = rad;
        }
        void SetSinWaveFacter(float fact){
            sinWaveFacter = fact;
        }
        void SetCosWaveFacter(float fact){
            cosWaveFacter = fact;
        }

        float GetPolyWidth(){ return polyW; }
        float GetPolyHeight(){ return polyH; }
        float GetTextureWidth(){ return texW; }
        float GetTextureHeight(){ return texH; }
        
        int GetTextureHandle(){ return texture; }

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

    // �ό`�̊�Ɏg���ėp�ϐ��B
    // SetFacter�֐��Ŏw�肷��B
    float       facterX;
    float       facterY;

    // �p�x�ό`�̊�Ɏg���ėp�ϐ�
    float       radX, radY;

    // �k���g��̊�Ɏg���ėp�ϐ�
    float       scaleX, scaleY;

    // �G�t�F�N�g�̃A���t�@�l 0~1.0f
    float       alpha;

    // �G�t�F�N�g�̏o�͐�B�@-1�ł����hDrawWindow���o�͐�
    int outScreen;
    bool isCreatedOutScreen;

    // �G�t�F�N�g�Ŏg�p����摜�n���h���@BGEffect�̉摜������Ɏg���܂킵�����Ƃ��Ɏg�p����B
    int inScreen;

    // �G�t�F�N�g�Ŏg�p����e���|�����X�N���[�� �ꕔ�Ŏg�p����B
    int tempScreen;

    // �G�t�F�N�g�Ŏg�p����obj�̔z��
    std::vector< BackGroundEffect::Object* > obj;

public:

	// �R���X�g���N�^
	Game_BGEffect();

	// �^�C�vID��ύX����B
	// �^�C�vID���Ƃ̏������������܂ށB
    bool SetTypeID(WORD id);

	// �^�C�vID���擾����B
	WORD GetTypeID(){ return typeID; }

	// �p�����[�^��ύX����B
	void SetParam(int p){ param = p; }

	// �p�����[�^���擾����B
	int GetParam(){ return param; }

	// �^�C�vID�ƃp�����[�^���܂Ƃ߂ăZ�b�g����B
	bool SetTypeID(WORD id, int param){ SetParam(param); return SetTypeID(id); }

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
    void SetRandTime(){ time = GetRand(32767); }

	// ��ʒu��������B
	void SetPosition(float _x, float _y){ posX = _x; posY = _y; }
    // �ό`��̗v�f��������B
    void SetFacter(float _x, float _y){ facterX = _x; facterY = _y; }
    // �ό`�p�x�̗v�f��������B
    void SetRadian(float x, float y){ radX = x; radY = y; }
    // �k���g��̗v�f��������B
    void SetScale(float x, float y){ scaleX = x; scaleY = y; }
    // �A���t�@�l��������
    void SetAlpha(float a){ alpha = a; }

    // �o�͐�X�N���[����ݒ肷��
    void SetOutputScreen(int handle){ outScreen = handle; }
    // �o�͐�X�N���[�����쐬����B
    int CreateOutputScreen(int w,int h){
        if (isCreatedOutScreen) DeleteGraph(outScreen);
        outScreen = MakeScreen(w, h, true);
        isCreatedOutScreen = true;
        return outScreen;
    }
    // �o�͐�X�N���[���̎擾
    int GetOutputScreen(){ return outScreen; }

    // �g�p����摜��ݒ肷�� type�ɂ���Ă͎g�p���Ȃ��B
    // �g�p����ꍇ��SetTypeID���Ăяo���O�ɌĂԂ��ƁB
    void SetInputScreen(int handle){ inScreen = handle; }
    
    


};



#endif // GAME_BGEFFECT_H