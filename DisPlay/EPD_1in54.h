#ifndef __EPD_1IN54_H_
#define __EPD_1IN54_H_

#include "DEV_Config.h"

// Display resolution
#define EPD_1IN54_WIDTH		200
#define EPD_1IN54_HEIGHT		200


void EPD_1IN54_Init(void);
void EPD_1IN54_Init_updown(void);
void EPD_1IN54_Init_Partial(void);
void EPD_1IN54_Clear(void);
void EPD_1IN54_Display(UBYTE *Image);
void EPD_1IN54_DisplayPart(UBYTE *Image);
void EPD_1IN54_Image_Display(UBYTE *Image);
void EPD_1IN54_DisplayPartBaseImage(UBYTE *Image);
void EPD_1IN54_Sleep(void);



#endif
