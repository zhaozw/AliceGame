// Scene_DollCreate.cpp

#include "Scene_DollCreate.h"
#include "Record_AliceInfo.h"
#include "GRecord_Others.h"
#include "Func_Graphics.h"
#include "Func_MyGraphic.h"
#include "Static_AliceDoll.h"
#include "Image.h"
#include "DXFont.h"
#include "WindowSkin.h"
#include "TempData.h"

extern Image			g_image;
extern DXFont			g_font;
extern WindowSkins		g_wndSkins;
extern TempData			g_temp;
extern Record_AliceInfo	r_aliceInfo;
extern GRecord_Others	gr_others;

#define DRAW_DOLL_CENTER_X		575		// �l�`�̕`��ʒu 

Scene_DollCreate::Scene_DollCreate():Scene_Base(),
	s_group(DOLL_GROUP_NUM), s_attr(DOLL_ATTR_NUM-1, 0, false){
		// �eSelectable�̏�����
		for(int t=0; t<DOLL_GROUP_NUM; t++){
			s_type[t].maxSize = DOLL_TYPE_PER_GROUP;
			s_type[t].index = 0;
			s_type[t].canWrap = true;
			s_type[t].isVirtical = false; // ���L�[�Ől�`�̐؂�ւ�
		}
}

bool Scene_DollCreate::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	state = SCNSTATE_DOLLCREATE_CHOOSETYPE;
	// �I��s�\�Ȑl�`�̑I�������Z�b�g
	for(int t=0; t<DOLL_GROUP_NUM; t++){
		for(int n=0; n<DOLL_TYPE_PER_GROUP; n++){
			if(!r_aliceInfo.GetHaveDollRecepe(t*DOLL_TYPE_PER_GROUP+n+1)){
				s_type[t].isActive[n] = false; // ���L�[�Ől�`�̐؂�ւ�
			}
		}
	}

	for(int n=0; n<DOLL_ATTRSTONE_CREATE; n++){
		attrStones[n] = DOLL_ATTR_NONE;
	}
	cntAttrStone = 0;

	// �E�B���h�E�̏�����
	InitWindow();
	return true;
}

bool Scene_DollCreate::InitWindow(){
	WINDOWAREA	frameArea(0, 0, 300, 300);
	WINDOWAREA	contentArea(16, 16, 300-32, 300-32);
	WINDOWFONT	font(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4,
		WINDOWFONT_DEFCOLOR, WINDOWFONT_DEFICOLOR, WINDOWFONT_DEFNCOLOR);
		
	// �͂��E�������E�B���h�E�̏�����
	w_yesno.Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, contentArea, font,
		true);
	w_yesno.SetTitle(_T("����Ől�`���쐬���܂����H"), g_font.hInfo, FONTSIZE_INFO+16);
	w_yesno.SetPositionH(WND_WIDTH/2);		// ��ʒ����ɑ�����
	w_yesno.SetPositionV(WND_HEIGHT/2);
	return true;
}


bool Scene_DollCreate::Terminate(){

	return true;
}

int Scene_DollCreate::Update(){
	int index=0;
	if(!SceneIsReserved()){
		switch(state){
		case SCNSTATE_DOLLCREATE_CHOOSETYPE:
			switch(s_group.Move()){
			case SELECT_CHOOSE:
				// �����I����
				SetState(SCNSTATE_DOLLCREATE_CHOOSESTONE);
				ResetAttrStones();
				break;
			case SELECT_CANCEL:
				// �L�����v��ʂɖ߂�
				ReserveScene(SCENE_CAMP, 20);
				break;
			default:
				// �^�C�v�̑I��
				s_type[s_group.index].Move();
			}
			break;
		case SCNSTATE_DOLLCREATE_CHOOSESTONE:
			switch(s_attr.Move()){
			case SELECT_CHOOSE:
				if(r_aliceInfo.GetPieceNum(s_group.index, s_attr.index) > 0){
					// �������������̐΂�I��
					SetAttrStone(s_group.index, s_attr.index+1, cntAttrStone);
					cntAttrStone++;
					if(cntAttrStone == DOLL_ATTRSTONE_CREATE){
						// ����������ł������ǂ����̊m�F
						SetState(SCNSTATE_DOLLCREATE_ASKCREATE);
						w_yesno.SetVisible(true);
						w_yesno.Open();
					}
				}else{
					// ���̐΂�I���ł��Ȃ�
				}
				break;
			case SELECT_CANCEL:
				if(cntAttrStone > 0){
					ResetAttrStone(cntAttrStone-1);
					cntAttrStone--;
				}else{
					// �^�C�v�I����ʂɖ߂�
					ResetAttrStones();
					SetState(SCNSTATE_DOLLCREATE_CHOOSETYPE);
				}
				break;
			}
			break;
		case SCNSTATE_DOLLCREATE_ASKCREATE:
			w_yesno.Update();
			if(w_yesno.GetState() == Window_Base::CLOSED){
				// ���肳�ꂽ�ꍇ
				switch(w_yesno.GetResult()){
				case WINDOW_YESNO_YES:
					// �l�`���쐬����
					RegisterNewDoll();
					// �V�[���ڍs
					ReserveScene(SCENE_DOLLBIRTH, 40);
					break;
				case WINDOW_YESNO_NO:
					SetState(SCNSTATE_DOLLCREATE_CHOOSESTONE);
					ResetAttrStone(DOLL_ATTRSTONE_CREATE-1);
					break;
				}
			}
			break;
		}
	}
	return SCENE_NONE;
}

void Scene_DollCreate::Draw() const{
	for(int g=0; g<DOLL_GROUP_NUM; g++){
		DrawEachGroup(50+0, 30+(EACHGROUP_HEIGHT+EACHGROUP_MARGIN)*g, g+1,
			s_group.index == g);
	}
	int index;
	// �l�`�C���X�g�̕`��
	DrawDollIllust(DRAW_DOLL_CENTER_X, 250, 
		DOLL_TYPE_PER_GROUP*s_group.index+s_type[s_group.index].index+1,
		DOLL_ATTR_NONE, 0.8, 0);
	// �����̕�΂̕`��
	DrawAttrStones();
	// �l�`�A�C�R���̕`��
	for(int n=0; n<DOLL_TYPE_PER_GROUP; n++){
		index = DOLL_TYPE_PER_GROUP*s_group.index+n+1;
		if(r_aliceInfo.GetHaveDollRecepe(index)){
			if(s_type[s_group.index].index == n){
				SetDrawBright(255, 255, 255);
			}else{
				SetDrawBright(128, 128, 128);
			}
			DrawDollIcon(400+n*128, 420, index, DOLL_ATTR_NONE, DOLL_FACE_NORMAL);
		}else{
			SetDrawBright(128, 128, 128);
			DrawDollIcon(400+n*128, 420, index, DOLL_ATTR_NONE, DOLL_FACE_DAMAGE);
		}
		ResetDrawARGB();
	}
	DrawReserveFade();
	// �E�B���h�E�̕`��
	w_yesno.Draw();
	// �������̕`��
	DrawAccount();
}

void Scene_DollCreate::DrawEachGroup(int x, int y, BYTE group, bool focused) const{
	int n=0;
	DrawBox(x, y, x+EACHGROUP_WIDTH, y+EACHGROUP_HEIGHT,
		focused ? GetColor(255, 255, 255) : GetColor(64, 64, 64), 0);
	// �t�H�[�J�X���������Ă���ꍇ�A�l�p�`�̕`��
	if(s_group.index+1 == group){
		switch(state){
		case SCNSTATE_DOLLCREATE_CHOOSESTONE:
			DrawAttrStoneFocus(
				x+3*s_attr.index*SIZE_ATTRICON,
				y+30);
			break;
		}
	}
	for(BYTE a=0; a<DOLL_ATTR_NUM-1; a++){
		// �����̕`��
		DrawGroupName(x, y, group, g_font.hInfo);
		// �A�C�R���̕`��
		DrawAttrStone(x+72*a+12+4, y+30+12,
			group, a+1, (float)SIZE_ATTRICON/SIZE_ATTRSTONE);
		// �����Ă��錇�Ђ̌��̕`��
		n = r_aliceInfo.GetPieceNum(group-1, a);
		DrawNum(n,
			x+3*a*SIZE_ATTRICON+SIZE_ATTRICON+NUMBER_I_WIDTH+4, y+30,
			g_image.chars.number_i,
			NUMBER_I_WIDTH, 2, ALIGN_CENTER, true);
	}
}

void Scene_DollCreate::DrawAttrStones() const{
	for(int n=0; n<DOLL_ATTRSTONE_CREATE; n++){
		DrawAttrStone(
			DRAW_DOLL_CENTER_X + 100*(n-1),
			400, s_group.index+1, attrStones[n]);
	}
}

void Scene_DollCreate::DrawAttrStoneFocus(int x, int y) const{
	DrawBox(x, y, x+3*SIZE_ATTRICON, y+NUMBER_I_HEIGHT, GetColor(255,255,255), 0);
}

void Scene_DollCreate::DrawAccount() const{
	const TCHAR acc[][128] = {
		_T("�쐬����l�`�̎�ނ�I�����ĉ�����"),
		_T("�l�`�Ɏg�p�����΂̂������3�I��ŉ�����"),
		_T("")
	};

	TCHAR buf[128];
	strcpy_s(buf, 128-1, acc[state]);
	int w = GetDrawStringWidthToHandle(buf, strlen(buf), g_font.hInfo);
	DrawStringToHandle(
		(WND_WIDTH-w)/2, WND_HEIGHT-FONTSIZE_INFO-2,
		buf, GetColor(255,255,255), g_font.hInfo);
}

void Scene_DollCreate::ResetAttrStones(){
	cntAttrStone = 0;
	for(int n=0; n<DOLL_ATTRSTONE_CREATE; n++){
		ResetAttrStone(n);
	}
}

void Scene_DollCreate::SetAttrStone(BYTE group, BYTE attr, int pos){
	attrStones[pos] = attr;
	r_aliceInfo.ReducePieceNum(group, attr-1);
}

void Scene_DollCreate::ResetAttrStone(int pos){
	// ��ԍŌ�ɑI�񂾐΂��L�����Z������
	BYTE attr = attrStones[pos];
	if(attr != DOLL_ATTR_NONE){
		// �Y�����錇�Ђ̐��𑝂₷
		r_aliceInfo.AddPieceNum(s_group.index, attr-1);
		// ���Ђ��������
		attrStones[pos] = DOLL_ATTR_NONE;
	}
}

void Scene_DollCreate::RegisterNewDoll(){
	// �l�`�̎��
	g_temp.dollData.SetType(DOLL_TYPE_PER_GROUP*s_group.index
		+s_type[s_group.index].index+1);
	// ���x���ƌo���l
	g_temp.dollData.SetLevel(1);
	g_temp.dollData.SetExp(0);
	// �������x��
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		g_temp.dollData.SetGrowthLevel(n, 0);
		g_temp.dollData.SetPotentialLevel(n, 0);
	}
	// �A���X��ID
	g_temp.dollData.SetAliceID(gr_others.GetAliceID());
	// �V���A���i���o�[
	g_temp.dollData.SetID(gr_others.GetDollID());
	// �����X�g�[��
	for(int n=0; n<DOLL_ATTRSTONE_CREATE; n++){
		if(n < DOLL_ATTRSTONE_CREATE){
			g_temp.dollData.SetAttrStone(n, attrStones[n]);
		}else{
			g_temp.dollData.SetAttrStone(n, DOLL_ATTR_NONE);
		}
	}
}