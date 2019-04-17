#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <jpeg/jpgogc.h>
#include <unistd.h>
#include <fat.h>
#include <wiiuse/wpad.h>

//cursor mode (img vs dot)?
//move more to init or just separate functions
//tic tac toe
//connect 4
//4 player color grab game?
//controller testing
//target shooting

static u32 *xfb;
static GXRModeObj *rmode;

JPEGIMG cursor;
extern char cursordata[];
extern int cursorlength;

/**
 * Initializes Picture data
 */
void PictureInit(){
    memset(&cursor, 0, sizeof(JPEGIMG));

    cursor.inbuffer = cursordata;
    cursor.inbufferlength = cursorlength;

    JPEG_Decompress(&cursor);
}

/**
 * Initialize video, controller, and picture functionality.
 */
void Init(){

	VIDEO_Init();
	PAD_Init();
	WPAD_Init();
	PictureInit();

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

/**
 * Draws a horizonal line.
 * @param x1 :first x position
 * @param x2 :second x position
 * @param y :y position
 * @param color :color of the line
 */
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

/**
 * Draws a vertical line.
 * @param x : x position
 * @param y1 :first y position
 * @param y2 :second y position
 * @param color :color of the line
 */
void DrawVLine(int x, int y1, int y2, int color){
	int i;
	x >>= 1;
	for(i = y1; i <= y2; i++){
		u32 *tmpfb = xfb;
		tmpfb[x + (640 * i) / 2] = color;
	}
}

/**
 * Draws a box on screen.
 * @param x1 :x cord 1
 * @param y1 :y cord 1
 * @param x2 :x cord 2
 * @param y2 :y cord 2
 * @param color :color of the box lines
 */
void DrawBox(int x1, int y1, int x2, int y2, int color){
	DrawHLine(x1, x2, y1, color);
	DrawHLine(x1, x2, y2, color);
	DrawVLine(x1, y1, y2, color);
	DrawVLine(x2, y1, y2, color);
}

/**
 * Displays a given JPEG image.
 * @param jpeg :the image name
 * @param x :top left x position
 * @param y :top left y position
 */
void DisplayJPEG(JPEGIMG jpeg, int x, int y) {

    unsigned int *jpegout = (unsigned int *) jpeg.outbuffer;

    int i,j;
    int height = jpeg.height;
    int width = jpeg.width / 2;
    for(i=0;i<=width;i++)
        for(j=0;j<=height-2;j++)
            xfb[(i+x)+320*(j+16+y)]=jpegout[i+width*j];
}

/**
 * Draws the cursor as an image
 * @param x :top left x position
 * @param y :top left y position
 * @param img :image to be drawn
 */
void DrawPictureCursor(int x, int y, JPEGIMG img){
    DisplayJPEG(img, x, y);
}


int main(){
    //Initialization
	Init();

    //position of the cursor
	int cursorPosX = 220;
	int cursorPosY = 160;

	bool ClearFrame = false;
	//controls what input i want to use for the dol make (stack will
	//dump if both types of inputs are trying to be noticed)
	bool gcControllerInput = true;

	while(1){

	    if (ClearFrame) {
            VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);
        }

	    //GAMECUBE INPUT
	    if (gcControllerInput) {
            PAD_ScanPads();

            //Are any buttons on controller 1 (port #2) being pressed?
            u16 buttonDown = PAD_ButtonsDown(1);
            u16 buttonHeld = PAD_ButtonsHeld(1);
            u16 buttonUp = PAD_ButtonsUp(1);

            if (PAD_StickY(1) > 18) {
                cursorPosY--;
            }
            if (PAD_StickY(1) < -18) {
                cursorPosY++;
            }
            if (PAD_StickX(1) > 18) {
                cursorPosX++;
            }
            if (PAD_StickX(1) < -18) {
                cursorPosX--;
            }
            if (PAD_BUTTON_START & buttonDown) {
                exit(0);
            }
            if (PAD_BUTTON_A & buttonDown) {
                printf("a \n");
            }
            if (PAD_BUTTON_B & buttonDown) {
                printf("b \n");
            }
            if (PAD_BUTTON_X & buttonDown) {
                printf("x \n");
            }
            if (PAD_BUTTON_Y & buttonDown) {
                printf("y \n");
            }
            if (PAD_TRIGGER_Z & buttonDown) {
                printf("z \n");
            }
            if (PAD_TRIGGER_L & buttonDown) {
                printf("LTRIG  \n");
            }
            if (PAD_TRIGGER_R & buttonDown) {
                printf("RTRIG  \n");
            }
            // code not working: idk how to properly call for c-stick inputs
//        if (PAD_SubstickY(0) > 18){
//            printf("subUP");
//        }
//        if (PAD_SubstickY(0) < -18 ){
//            printf("subDOWN");
//        }
//        if (PAD_SubstickX(0) < -18 ){
//            printf("subLEFT");
//        }
//        if (PAD_SubstickX(0) > 18 ){
//            printf("subRIGHT");
//        }
            if (PAD_TRIGGER_L & buttonDown) {
                printf("trigL  \n");
            }
            if (PAD_TRIGGER_R & buttonDown) {
                printf("trigR  \n");
            }
        }

	    //if (!gcControllerInput) {}
            //WII INPUT
            WPAD_ScanPads();

            u32 buttonDownW = WPAD_ButtonsDown(WPAD_CHAN_0);
            u32 buttonHeldW = WPAD_ButtonsHeld(WPAD_CHAN_0);
            u32 buttonUpW = WPAD_ButtonsUp(WPAD_CHAN_0);


            if (buttonDownW & WPAD_BUTTON_A) {
                printf("WiiA\n");
            }
            if (buttonHeldW & WPAD_BUTTON_A) {
                printf("WiiA Held\n");
            }
            if (buttonUpW & WPAD_BUTTON_A) {
                printf("WiiAReleased\n");
            }
            if (buttonDownW & WPAD_BUTTON_HOME) {
                exit(0);
            }


		//dot cursor
		//DrawBox(cursorPosX, cursorPosY, cursorPosX + 1, cursorPosY + 1, COLOR_WHITE);

		//img cursor
		//DrawPictureCursor(cursorPosX, cursorPosY, cursor);

		VIDEO_WaitVSync();
	}
	return 0;
}