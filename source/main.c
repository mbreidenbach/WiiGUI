#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <jpeg/jpgogc.h>
#include <unistd.h>
#include <fat.h>
//cursor mode (img vs dot)?
//move more to init or just separate functions
//tic tac toe
//connect 4
//4 player color grab game?
//controller testing
//target shooting

static u32 *xfb;
static GXRModeObj *rmode;

void Init(){

	VIDEO_Init();
	PAD_Init();

	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb, 20, 20, rmode -> fbWidth, rmode -> xfbHeight, rmode -> fbWidth*VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode -> viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

void DrawHLine(int x1, int x2, int y, int color){
	int i;
	y = 320 * y;
	x1 >>= 1;
	x2 >>= 1;
	for(i = x1; i <= x2; i++){
		u32 *tmpfb = xfb;
		tmpfb[y+i] = color;
	}
}

void DrawVLine(int x, int y1, int y2, int color){
	int i;
	x >>= 1;
	for(i = y1; i <= y2; i++){
		u32 *tmpfb = xfb;
		tmpfb[x + (640 * i) / 2] = color;
	}
}

void DrawBox(int x1, int y1, int x2, int y2, int color){
	DrawHLine(x1, x2, y1, color);
	DrawHLine(x1, x2, y2, color);
	DrawVLine(x1, y1, y2, color);
	DrawVLine(x2, y1, y2, color);
}

void DrawPictureCursor(int x, int y, JPEGIMG img){

}


int main(){
	Init();

	int cursorPosX = 100;
	int cursorPosY = 100;

	while(1){

		VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);

		PAD_ScanPads();

		//Are any buttons on controller 0 being pressed?
		u16 buttonDown = PAD_ButtonsDown(0);
		u16 buttonHeld = PAD_ButtonsHeld(0);
		u16 buttonUp = PAD_ButtonsUp(0);

		if (PAD_StickY(0) > 18) {
			cursorPosY--;
		}
		if (PAD_StickY(0) < -18) {
			cursorPosY++;
		}
		if (PAD_StickX(0) > 18) {
			cursorPosX++;
		}
		if (PAD_StickX(0) < -18) {
			cursorPosX--;
		}
		if (PAD_BUTTON_START & buttonDown){
			exit(0);
		}

		//dot cursor
		DrawBox(cursorPosX, cursorPosY, cursorPosX + 1, cursorPosY + 1, COLOR_WHITE);

		VIDEO_WaitVSync();
	}
	return 0;
}