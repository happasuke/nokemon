#include "DxLib.h"
#include "stdlib.h"
#include "stdio.h"

#define mapHeight 16
#define mapWidth 22
#define fieldHeight 8
#define fieldWidth 11
#define wait 10

int whatkey();

int field[mapHeight][mapWidth] = {
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 4 },
	{ 4, 11, 11, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4 },
	{ 4, 2, 2, 4, 4, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 4 },
	{ 4, 2, 2, 11, 11, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 5, 5, 5, 4 },
	{ 4, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 4, 4 },
	{ 4, 5, 5, 5, 5, 5, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 4, 4 },//8
	{ 4, 4, 4, 4, 4, 4, 2, 1, 1, 1, 9, 1, 1, 2, 2, 2, 2, 2, 11, 11, 4, 4 },
	{ 4, 4, 4, 11, 11, 11, 2, 1, 1, 1, 1, 1, 1, 2, 2, 3, 2, 2, 2, 2, 11, 4 },
	{ 4, 4, 4, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 3, 2, 2, 2, 2, 2, 2, 2, 4 },
	{ 4, 4, 11, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4 },
	{ 4, 11, 1, 1, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4 },
	{ 4, 5, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4 },
	{ 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4 },
	{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 }//16
};

int se, bgm;
int g[10], b[12], walk = 0, px = 0, py = 0, pstate = 9, seeMapY = 0, seeMapX = 0;
bool walkNumber = true;

void init(){
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)exit(0);
	SetTransColor(255, 255, 255);
	LoadDivGraph("tr.bmp", 10, 10, 1, 16, 32, g, FALSE);
	LoadDivGraph("pic1x1.bmp", 12, 6, 2, 16, 16, b, FALSE);

	se = LoadSoundMem("F:/pokemodule/pon.wav");
	bgm = LoadSoundMem("F:/pokemodule/endo.wav");
}

void DrawBackField(){
	for (int y = seeMapY; y<mapHeight; y++){
		for (int x = seeMapX; x<mapWidth; x++){
			switch (field[y][x]){
			case 0:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[0], FALSE); break;
			case 1:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[1], FALSE); break;
			case 2:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[2], FALSE); break;
			case 3:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[3], FALSE); break;
			case 4:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[4], FALSE); break;
			case 5:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[5], FALSE); break;
			case 7:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[7], FALSE); break;
			case 9:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[9], FALSE); break;
			case 11:DrawExtendGraph(x * 64 - 32 - px, y * 64 - py, x * 64 + 32 - px, y * 64 + 64 - py, b[11], FALSE); break;
			default:break;
			}
		}
	}
}

int DrawPlayer(int state){

	int AnimationTime = 16;
	int dev = 64 / AnimationTime;

	switch (state){
	case 1:state = 8;
		if (field[py / 64 + 3][px / 64 + 5]>2){ dev = 0; PlaySoundMem(se, DX_PLAYTYPE_BACK); }

		for (int i = 0; i<AnimationTime; i++, py -= dev){
			SetDrawScreen(DX_SCREEN_BACK);
			ClearDrawScreen();

			DrawBackField();

			if (i>AnimationTime / 2){
				state = 8;
			}
			else{
				if (walkNumber == true)
					state = 2;
				else
					state = 3;
			}

			DrawExtendGraph(64 * 5 - 32, 64 * 3, 64 * 5 + 64 - 32, 64 * 3 + 128, g[state], TRUE);
			ScreenFlip();
			WaitTimer(wait);
		}

		dev = 64 / AnimationTime;
		pstate = state;
		break;

	case 2:state = 9;
		if (field[py / 64 + 5][px / 64 + 5]>2){ dev = 0; PlaySoundMem(se, DX_PLAYTYPE_BACK); }

		for (int i = 0; i<AnimationTime; i++, py += dev){
			SetDrawScreen(DX_SCREEN_BACK);
			ClearDrawScreen();

			DrawBackField();

			if (i>AnimationTime / 2){
				state = 9;
			}
			else{
				if (walkNumber == true)
					state = 0;
				else
					state = 1;
			}

			DrawExtendGraph(64 * 5 - 32, 64 * 3, 64 * 5 + 64 - 32, 64 * 3 + 128, g[state], TRUE);
			ScreenFlip();
			WaitTimer(wait);
		}

		dev = 64 / AnimationTime;
		pstate = state;
		break;

	case 3:state = 7;
		if (field[py / 64 + 4][px / 64 + 4]>2){ dev = 0; PlaySoundMem(se, DX_PLAYTYPE_BACK); }

		for (int i = 0; i<AnimationTime; i++, px -= dev){
			SetDrawScreen(DX_SCREEN_BACK);
			ClearDrawScreen();

			DrawBackField();

			if (i>AnimationTime / 2){
				state = 7;
			}
			else{
				state = 5;
			}

			DrawExtendGraph(64 * 5 - 32, 64 * 3, 64 * 5 + 64 - 32, 64 * 3 + 128, g[state], TRUE);
			ScreenFlip();
			WaitTimer(wait);
		}
		dev = 64 / AnimationTime;
		pstate = state;
		break;

	case 4:state = 6;
		if (field[py / 64 + 4][px / 64 + 6]>2){ dev = 0; PlaySoundMem(se, DX_PLAYTYPE_BACK); }

		for (int i = 0; i<AnimationTime; i++, px += dev){
			SetDrawScreen(DX_SCREEN_BACK);
			ClearDrawScreen();

			DrawBackField();

			if (i>AnimationTime / 2){
				state = 6;
			}
			else{
				state = 4;
			}

			DrawExtendGraph(64 * 5 - 32, 64 * 3, 64 * 5 + 64 - 32, 64 * 3 + 128, g[state], TRUE);
			ScreenFlip();
			WaitTimer(wait);
		}

		dev = 64 / AnimationTime;
		pstate = state;
		break;

	case 0:switch (pstate){
	case 8:state = 8; break;
	case 9:state = 9; break;
	case 6:state = 6; break;
	case 7:state = 7; break;
	default:state = 5; break;
	}
		   break;

	default:return -1;
	}

	DrawExtendGraph(64 * 5 - 32, 64 * 3, 64 * 5 + 64 - 32, 64 * 3 + 128, g[state], TRUE);
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	int state = 9;
	init();

	PlaySoundMem(bgm, DX_PLAYTYPE_BACK);

	while (ProcessMessage() == 0){
		printf("im here");
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

		DrawBackField();
		if (walk == 0)state = whatkey();
		if (DrawPlayer(state) != 0)break;

		ScreenFlip();
		WaitTimer(wait);
	}


	DxLib_End();
	return 0;
}

int whatkey(){

	if (CheckHitKey(KEY_INPUT_W)){
		walkNumber = !walkNumber;
		return 1;
	}
	else if (CheckHitKey(KEY_INPUT_S)){
		walkNumber = !walkNumber;
		return 2;
	}
	else if (CheckHitKey(KEY_INPUT_A)){
		walkNumber = !walkNumber;
		return 3;
	}
	else if (CheckHitKey(KEY_INPUT_D)){
		walkNumber = !walkNumber;
		return 4;
	}
	else{
		return 0;
	}
}