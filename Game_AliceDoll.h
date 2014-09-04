#ifndef GAME_ALICEDOLL_H
#define GAME_ALICEDOLL_H

// �A���X�̐l�`�Ɋւ���N���X���L�q����t�@�C���B
// �퓬���ɂ�����l�`�Ɋւ��Ă͕ʂ̃t�@�C���ň����B

#include <Windows.h>
#include "Static_AliceDoll.h"
#include "Static_AliceInfo.h"

// �p�����[�^�����߂�e���x���̍\���́B
// �l�`�̊e�p�����[�^�͂��̃��x���ƒʏ�̃��x����p���Čv�Z�����O���[�o�����x����
// �l�`�̎�ނɂ���Č��肳���B
typedef struct ParamLevel{
	DWORD potential;		// �������x���B
						// �l�`�̍쐬���Ɍ��肳��A
						// ���̌�͕ω����Ȃ��B
	DWORD growth;			// �������x���B
						// ���x���A�b�v����A�C�e���ɂ����
						// �{�[�i�X���ɑ�����B
} PARAMLEVEL;

// �A���X�̐l�`�̃f�[�^�̂����A
// �Z�[�u�f�[�^�Ɋ܂߂�K�v�̂���f�[�^��ێ�����\���́B
// Game_AliceDoll_Essense�N���X�ɕێ������B
typedef struct Game_AliceDoll_Essence_Data{
	DWORD		aliceID;			// ���̐l�`���쐬�����A���X��ID�B
	DWORD		id;					// �l�`��ID�B�Q�[���S�̂�ʂ��Ēʂ��ԍ��Ŋ���U����B
									// aliceID��id������̐l�`�͋�ʂ���Ȃ��B
	int			chapter;			// ���̐l�`���쐬���ꂽ�͂̔ԍ��B
	WORD		name[MAX_DOLLNAME];	// �l�`�̖��O�B
	BYTE		type;				// �����ł́A��C�l�`�Ȃǐl�`�̎�ށB
									// �l�`�̎�ށi�o�����X�^�C�v�Ȃǂ̃^�C�v��"group"�j
	WORD		level;				// �S�̂Ƃ��Ẵ��x��
	DWORD		exp;				// �ώZ�̌o���l�B
	int			hp;					// ���݂�HP�B�i�ő�HP�Ƃ͕ʂ̊Ǘ��j
	PARAMLEVEL	paramLevel[DOLL_PARAM_MAX];	// �p�����[�^���Ƃ̃��x��
	BYTE		attrStone[DOLL_ATTRSTONE_NUM]; // �����X���b�g
	WORD		skillID[DOLL_SKILL_MAX];	// �o���Ă���X�L���̔z��

	Game_AliceDoll_Essence_Data(){
		aliceID = 0;
		id = 0;
		chapter = 0;
		type = DOLL_TYPE_UNDIFINED;
		level = 1;
		exp = 0;
		for(int n=0; n<DOLL_PARAM_MAX; n++){
			paramLevel[n].potential = 0;
			paramLevel[n].growth = 0;
		}
		for(int n=0; n<DOLL_ATTRSTONE_NUM; n++){
			attrStone[n] = 0;
		}
		for(int n=0; n<MAX_DOLLNAME; n++){
			name[n] = 0x00;
		}
		for(int n=0; n<DOLL_SKILL_MAX; n++){
			skillID[n] = 0;
		}
	}
} GAME_ALICEDOLL_ESSENCE_DATA;

// �A���X�̐l�`�̃f�[�^�̂����A
// �Z�[�u�f�[�^�Ɋ܂߂�K�v�̂���f�[�^�������N���X�B
// ���X�g�Ƃ��Ĉ����֌W��f�[�^�����ׂč\���̓��ɕێ����Ă���B
class Game_AliceDoll_Essence{
private:
	GAME_ALICEDOLL_ESSENCE_DATA		data;	// �f�[�^�B
public:
	static DWORD dataSize;					// �f�[�^�T�C�Y�B
public:
	// �R���X�g���N�^
	Game_AliceDoll_Essence();
	// �f�X�g���N�^
	~Game_AliceDoll_Essence();
	// �R�s�[�R���X�g���N�^
	Game_AliceDoll_Essence(const Game_AliceDoll_Essence& i);
	// ������Z�q
	Game_AliceDoll_Essence &operator=(const Game_AliceDoll_Essence &i);

	// �A�N�Z�T
	DWORD		GetAliceID(){ return data.aliceID; };
	void		SetAliceID(DWORD _aliceID){ data.aliceID = _aliceID; };
	DWORD		GetID(){ return data.id; };
	void		SetID(DWORD _id){ data.id = _id; };
	BYTE		GetType(){ return data.type; };
	void		SetType(BYTE type){ data.type = type; };
	WORD		GetLevel(){ return data.level; };
	void		SetLevel(WORD level){ data.level = level; };
	DWORD		GetExp(){ return data.exp; };
	void		SetExp(DWORD exp){ data.exp = exp; };
	int			GetHP(){ return data.hp; };
	void		SetHP(int hp){ data.hp = hp; };
	// aliceID��id�̒l��p���ē���̐l�`���ǂ������擾����B
	bool		CheckSerial(DWORD aliceID, DWORD id){
		return (data.aliceID==aliceID && data.id==id); };

	// �������x�����擾�B
	DWORD		GetPotentialLevel(BYTE param){
		if(param >= DOLL_PARAM_MAX){
			return 0;
		}
		return data.paramLevel[param].potential;
	};

	// �������x�����擾�B
	DWORD		GetGrowthLevel(BYTE param){
		if(param >= DOLL_PARAM_MAX){
			return 0;
		}
		return data.paramLevel[param].growth;
	};

	// �������x�����Z�b�g�B
	void		SetPotentialLevel(BYTE param, DWORD level){
		if(param >= DOLL_PARAM_MAX){
			return;
		}
		data.paramLevel[param].potential = level;
	}
	// �������x�����Z�b�g�B
	void		SetGrowthLevel(BYTE param, DWORD level){
		if(param >= DOLL_PARAM_MAX){
			return;
		}
		data.paramLevel[param].growth = level;
	}
	BYTE		GetAttrStone(int pos){
		if(pos >= DOLL_ATTRSTONE_NUM || pos<0){
			return DOLL_ATTR_NONE;
		}
		return data.attrStone[pos];
	}
	void		SetAttrStone(int pos, BYTE attr){
		if(pos >= DOLL_ATTRSTONE_NUM || pos<0){
			return;
		}
		data.attrStone[pos] = attr;
	}
	WORD		GetSkillID(int index){
		if(index < 0 || index >= DOLL_SKILL_MAX){
			return 0;
		}
		return data.skillID[index];
	}
	void		SetSkillID(int index, WORD _skillID){
		if(index < 0 || index >= DOLL_SKILL_MAX){
			return;
		}
		data.skillID[index] = _skillID;
	}


	// �p�����[�^���Ƃ̃O���[�o�����x�����擾����֐�
	DWORD		GetGLevel(BYTE paramID) const;	// �e�p�����[�^
	DWORD		GetGeneralGLevel() const;		// �S�p�����[�^�̕���(�o���l�e�[�u���ȂǂɎg�p)

	// �l�`�̑������擾����֐��B
	// ��Ԃ�����̑���������Ԃ��B
	BYTE		GetAttr() const;

	// �Z�[�u�f�[�^�Ƃ��ĕۑ����邽�߂ɓ��e���o�C�g��ɕϊ�����֐�
	bool ConvertDataToBytes(LPBYTE p, DWORD size);

	// �Z�[�u�f�[�^����ǂݍ��ނ��߂ɓ��e���o�C�g�񂩂�ǂݍ��ފ֐�
	bool ConvertBytesToData(LPBYTE p, DWORD size);
};

// �A���X�̐l�`�̃f�[�^�̂����A
// �Z�[�u�f�[�^�Ɋ܂߂�K�v�̂Ȃ��f�[�^��ێ�����N���X�B
// ���ۂ͂����̃f�[�^�͌v�Z�ɂ���ĎZ�o���\�ł��邪�A
// �X�e�[�^�X��ʂȂǂŖ��t���[���v�Z����͖̂��ʂł��邽�߁A
// �X�e�[�^�X��ʂɂ����Ă͂��̃N���X�̃��X�g�Ƃ��Đl�`���Ǘ�����B
class Game_AliceDoll : public Game_AliceDoll_Essence{
	DWORD		param[DOLL_PARAM_MAX];	// �e�p�����[�^�̎��ۂ̒l
	DWORD		prevLevelExp;			// �O�̃��x���ɕK�v�Ȍo���l
										// (Lv4�ł���΁ALv1��Lv4�ɏオ��̂ɗv�����o���l�B
										// Lv1�̏�Ԃł�0�ł���B
	DWORD		nextLevelExp;			// ���̃��x���ɕK�v�Ȍo���l
										// (Lv4�ł���΁ALv1��Lv5�ɏオ��̂ɕK�v�Ȍo���l�B
										// ���ݍő僌�x���ł���ꍇ�͌Œ�l99999999�ƂȂ�B

};

#endif // GAME_ALICEDOLL_H
