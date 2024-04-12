#include "display.h"


void LED_DisPlay(void);
void EPD_1IN54_test(void);

uint8_t key_flag[3] = {0};



void epd1in54_showbmp(const uint8_t *nfcBuffer)
{     
    DEV_Module_Init();
    EPD_1IN54_Init();
    EPD_1IN54_Clear();  
    
    DEV_Delay_ms(500);	    
    UBYTE *BlackImage1;
    UWORD Imagesize = ((EPD_1IN54_WIDTH % 8 == 0)? (EPD_1IN54_WIDTH / 8 ): (EPD_1IN54_WIDTH / 8 + 1)) * EPD_1IN54_HEIGHT;
    if((BlackImage1 = (UBYTE *)malloc(Imagesize)) == NULL) 
        {
        return ;
        }
    Paint_NewImage(BlackImage1, EPD_1IN54_WIDTH, EPD_1IN54_HEIGHT, 90,    WHITE);
//                  图片指针          宽度             高度     旋转角度  填充颜色
    Paint_SelectImage(BlackImage1);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(nfcBuffer);

    EPD_1IN54_Image_Display(BlackImage1);
    DEV_Delay_ms(500);
         
    EPD_1IN54_Sleep();
    free(BlackImage1);
    BlackImage1 = NULL;
    // close 5V
    DEV_Module_Exit();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==GPIO_PIN_15)
  {
        key_flag[0]++;  
        key_flag[1]++;    
        key_flag[2]++;

        
  }
}

void EPD_1IN54_test(void)
{
	DEV_Module_Init();//接口高低电平初始化
    EPD_1IN54_Init();//  EPD_1IN54_FULL  0 全屏刷新      EPD_1IN54_PART  1   局部刷新
    EPD_1IN54_Clear();             //清屏
    DEV_Delay_ms(500);	
    //创建新的图像缓存
    UBYTE *BlackImage;
    UWORD Imagesize = ((EPD_1IN54_WIDTH % 8 == 0)? (EPD_1IN54_WIDTH / 8 ): (EPD_1IN54_WIDTH / 8 + 1)) * EPD_1IN54_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        return ;
    }

    Paint_NewImage(BlackImage, EPD_1IN54_WIDTH, EPD_1IN54_HEIGHT, 0, WHITE);
//	                   ↑              ↑               ↑         ↑     ↑
//                  图片指针          宽度             高度    旋转角度  填充颜色

	 Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    // 2.Drawing on the image
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 10, 20, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(170, 15, 170, 55, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(150, 35, 190, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawCircle(170, 35, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(170, 85, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(5, 85, "waveshare", &Font20, BLACK, WHITE);
    Paint_DrawNum(5, 110, 123456789, &Font20, BLACK, WHITE);

    Paint_DrawString_CN(5, 135,"你好abc", &Font12CN, BLACK, WHITE);
    Paint_DrawString_CN(5, 155, "微雪电子", &Font24CN, WHITE, BLACK);
    //Paint_DrawBitMap(panda);
	//Paint_DrawBitMap(nfcBuffer);

    EPD_1IN54_Image_Display(BlackImage);
    DEV_Delay_ms(1000);	
    free(BlackImage);
//   // 关闭5V，模块进入0功耗
    DEV_Module_Exit();
    
    return ;
	
}


void LED_DisPlay(void)   
{
    for(uint8_t i = 0; i < 3 ; i++)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET); //H-set,L-RESET
        DEV_Delay_ms(30);	
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
        DEV_Delay_ms(30);
    }
}



