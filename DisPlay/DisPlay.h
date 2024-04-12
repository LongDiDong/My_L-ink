#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "EPD_1in54.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "fonts.h"


extern uint8_t key_flag[3] ;



void EPD_1IN54_test(void);
void LED_DisPlay(void);
void epd1in54_showbmp(const uint8_t *nfcBuffer);

#endif

