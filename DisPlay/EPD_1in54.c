/*****************************************************************************
* | File      	:   EPD_1in54.C
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper
* | Info        :
*----------------
* |	This version:   V3.0
* | Date        :   2019-06-12
* | Info        :
******************************************************************************/
#include "EPD_1in54.h"
#include "Debug.h"
#include "epd_1in54.h"
static unsigned char EPD_1IN54_lut_full_update[] = {
0x80,	0x48,	0x40,	0x48,	0x48,	0x48,	0x48,	0x48,	0x48,	0x48,	0x48,	0x48,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0, //60
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,//67					
0x8,	0x1,	0x0,	0x8,	0x1,	0x0,	0x2,					
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,		//144			
0x22,	0x22,	0x22,	0x22,	0x22,	0x22,	0x0,	0x0,	0x0,  //153			
0x22,	0x17,	0x41,	0x0,	0x32,	0x20
};

static unsigned char EPD_1IN54_lut_partial_update[] = {
0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x40,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0xF,0x0,0x0,0x0,0x0,0x0,0x0,
0x1,0x1,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x22,0x22,0x22,0x22,0x22,0x22,0x0,0x0,0x0,
0x02,0x17,0x41,0xB0,0x32,0x28,
};

/******************************************************************************
���ܣ������λ
��Χ��
******************************************************************************/
static void EPD_1IN54_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(2);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
}

/******************************************************************************
���ܣ���������
��Χ��
	Reg : ����Ĵ���
******************************************************************************/
static void EPD_1IN54_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
���ܣ���������
��Χ��
     Data��д������
******************************************************************************/
static void EPD_1IN54_SendData(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
���ܣ��ȵ�busy_pin���
��Χ��
******************************************************************************/
void EPD_1IN54_ReadBusy(void)
{
    while(DEV_Digital_Read(EPD_BUSY_PIN) == 1) {      //LOW: ����, HIGH: æµ
        DEV_Delay_ms(10);
    }
}

/******************************************************************************
���ܣ�������ʾ����
��Χ��
******************************************************************************/
static void EPD_1IN54_SetWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    EPD_1IN54_SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
    EPD_1IN54_SendData((Xstart >> 3) & 0xFF);
    EPD_1IN54_SendData((Xend >> 3) & 0xFF);

    EPD_1IN54_SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
    EPD_1IN54_SendData(Ystart & 0xFF);
    EPD_1IN54_SendData((Ystart >> 8) & 0xFF);
    EPD_1IN54_SendData(Yend & 0xFF);
    EPD_1IN54_SendData((Yend >> 8) & 0xFF);
}


/******************************************************************************
���ܣ����ù��
��Χ��
******************************************************************************/
static void EPD_1IN54_SetCursor(UWORD Xstart, UWORD Ystart)
{
    EPD_1IN54_SendCommand(0x4E); // SET_RAM_X_ADDRESS_COUNTER
   // EPD_1IN54_SendData((Xstart >> 3) & 0xFF);
    EPD_1IN54_SendData((Xstart) & 0xFF);
    EPD_1IN54_SendCommand(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
    EPD_1IN54_SendData(Ystart & 0xFF);
    EPD_1IN54_SendData((Ystart >> 8) & 0xFF);
}

/******************************************************************************
���ܣ�������ʾ
��Χ��
******************************************************************************/
static void EPD_1IN54_TurnOnDisplay(void)
{
    EPD_1IN54_SendCommand(0x22); // DISPLAY_UPDATE_CONTROL_2
    EPD_1IN54_SendData(0xC7);
    EPD_1IN54_SendCommand(0x20); // MASTER_ACTIVATION
//    EPD_1IN54_SendCommand(0xFF); // TERMINATE_FRAME_READ_WRITE

    EPD_1IN54_ReadBusy();
}
/******************************************************************************
���ܣ������ֲ���ʾ
��Χ��
******************************************************************************/
static void EPD_1IN54_TurnOnDisplayPart(void)
{
    EPD_1IN54_SendCommand(0x22);
    EPD_1IN54_SendData(0xcF);  //��������
    EPD_1IN54_SendCommand(0x20);
    EPD_1IN54_ReadBusy();
}

static void EPD_1IN54_Lut(UBYTE *lut)
{
	EPD_1IN54_SendCommand(0x32);
	for(UBYTE i=0; i<153; i++)
		EPD_1IN54_SendData(lut[i]);
	EPD_1IN54_ReadBusy();
}
static void EPD_1IN54_SetLut(UBYTE *lut)
{
	EPD_1IN54_Lut(lut);
	
    EPD_1IN54_SendCommand(0x3f);
    EPD_1IN54_SendData(lut[153]);
	
    EPD_1IN54_SendCommand(0x03);
    EPD_1IN54_SendData(0x00); //lut[154]
	
    EPD_1IN54_SendCommand(0x04);
    EPD_1IN54_SendData(lut[155]);
	EPD_1IN54_SendData(0xA8);//lut[156]
	EPD_1IN54_SendData(lut[157]);
	
	EPD_1IN54_SendCommand(0x2c);
    EPD_1IN54_SendData(lut[158]); //
}

/******************************************************************************
���ܣ���ʼ������ֽ�Ĵ���
��Χ��
******************************************************************************/
void EPD_1IN54_Init(void)
{
    EPD_1IN54_Reset();
    
    EPD_1IN54_ReadBusy(); 
    EPD_1IN54_SendCommand(0x12);  //�����������
    EPD_1IN54_ReadBusy();
    
    EPD_1IN54_SendCommand(0x01); //Set gate driver    
    EPD_1IN54_SendData(0xC7);  /* 0xc7Ϊ200��200  ����ͼ���С */
    EPD_1IN54_SendData(0x00);  
    EPD_1IN54_SendData(0x01); //0x01 0x11Ϊ��������Ϊ�� //����ͼƬ�����µߵ�
    
    EPD_1IN54_SendCommand(0x11); //data entry mode
    EPD_1IN54_SendData(0x01);
//    EPD_1IN54_SendData(0x00); // GD = 0; SM = 0; TB = 0;
    EPD_1IN54_SetWindow(0, EPD_1IN54_HEIGHT-1, EPD_1IN54_WIDTH-1, 0);
    
    EPD_1IN54_SendCommand(0x3C); //���ñ߿���ɫ
    EPD_1IN54_SendData(0x01);  //0x01 ��ɫ

    EPD_1IN54_SendCommand(0x18); //�¶ȼ��
    EPD_1IN54_SendData(0x80);  //�ڲ��¶ȴ��������

    EPD_1IN54_SendCommand(0x22); // //Load Temperature and waveform setting.
    EPD_1IN54_SendData(0Xb1);
    EPD_1IN54_SendCommand(0x20);

    EPD_1IN54_SetCursor(0, EPD_1IN54_HEIGHT-1);
    EPD_1IN54_ReadBusy();

    EPD_1IN54_SetLut(EPD_1IN54_lut_full_update);
//    EPD_1IN54_SetLut(EPD_1IN54_lut_full_update2);

}

void EPD_1IN54_Init_updown(void)
{
    EPD_1IN54_Reset();
    
    EPD_1IN54_ReadBusy(); 
    EPD_1IN54_SendCommand(0x12);  //½øȫ²ΊýŤփ
    EPD_1IN54_ReadBusy();
    
    EPD_1IN54_SendCommand(0x01); //Set gate driver    
    EPD_1IN54_SendData(0xC7);  /* 0xc7Ϊ200¡Á200  ɨփͼϱ´󐡠*/
    EPD_1IN54_SendData(0x00);  
    EPD_1IN54_SendData(0x00); //0x01 0x11Ϊս£¬Ƥ˻Ϊ·´ //ɨփͼƬ¸øɏςµߵ¹
    
    EPD_1IN54_SendCommand(0x11); //data entry mode
    EPD_1IN54_SendData(0x01);
//    EPD_1IN54_SendData(0x00); // GD = 0; SM = 0; TB = 0;
    EPD_1IN54_SetWindow(0, EPD_1IN54_HEIGHT-1, EPD_1IN54_WIDTH-1, 0);
    
    EPD_1IN54_SendCommand(0x3C); //ɨփ±߿򑕉«
    EPD_1IN54_SendData(0x01);  //0x01 °׉«

    EPD_1IN54_SendCommand(0x18); //΂¶ȼ첢
    EPD_1IN54_SendData(0x80);  //Ě²¿΂¶ȴ«¸І÷¼첢

    EPD_1IN54_SendCommand(0x22); // //Load Temperature and waveform setting.
    EPD_1IN54_SendData(0Xb1);
    EPD_1IN54_SendCommand(0x20);

    EPD_1IN54_SetCursor(0, EPD_1IN54_HEIGHT-1);
    EPD_1IN54_ReadBusy();

    EPD_1IN54_SetLut(EPD_1IN54_lut_full_update);
//    EPD_1IN54_SetLut(EPD_1IN54_lut_full_update2);

}

void EPD_1IN54_Init_Partial(void)
{
	EPD_1IN54_Reset();
	EPD_1IN54_ReadBusy();
	
	EPD_1IN54_SetLut(EPD_1IN54_lut_partial_update);
	EPD_1IN54_SendCommand(0x37); 
	EPD_1IN54_SendData(0x00);  
	EPD_1IN54_SendData(0x00);  
	EPD_1IN54_SendData(0x00);  
	EPD_1IN54_SendData(0x00); 
	EPD_1IN54_SendData(0x00);  	
	EPD_1IN54_SendData(0x40);  
	EPD_1IN54_SendData(0x00);  
	EPD_1IN54_SendData(0x00);   
	EPD_1IN54_SendData(0x00);  
	EPD_1IN54_SendData(0x00);

	EPD_1IN54_SendCommand(0x3C); //BorderWavefrom
	EPD_1IN54_SendData(0x80);
	
	EPD_1IN54_SendCommand(0x22); 
	EPD_1IN54_SendData(0xc0); 
	EPD_1IN54_SendCommand(0x20); 
	EPD_1IN54_ReadBusy();
}

/******************************************************************************
���ܣ�����
��Χ��
******************************************************************************/
void EPD_1IN54_Clear(void)
{
    UWORD Width, Height;
    Width = (EPD_1IN54_WIDTH % 8 == 0)? (EPD_1IN54_WIDTH / 8 ): (EPD_1IN54_WIDTH / 8 + 1);
    Height = EPD_1IN54_HEIGHT;
    
    EPD_1IN54_SetWindow(0, 0, EPD_1IN54_WIDTH, EPD_1IN54_HEIGHT);
    for (UWORD j = 0; j < Height; j++) {
        EPD_1IN54_SetCursor(0, j);
        EPD_1IN54_SendCommand(0x24);
        for (UWORD i = 0; i < Width; i++) {
            EPD_1IN54_SendData(0XFF);
        }
    }
    EPD_1IN54_TurnOnDisplay();
}

/******************************************************************************
���ܣ���RAM�е�ͼ�񻺳������͵�e-Paper����ʾ
��Χ��
******************************************************************************/
void EPD_1IN54_Display(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_1IN54_WIDTH % 8 == 0)? (EPD_1IN54_WIDTH / 8 ): (EPD_1IN54_WIDTH / 8 + 1);
    Height = EPD_1IN54_HEIGHT;

    UDOUBLE Addr = 0;
    // UDOUBLE Offset = ImageName;
    EPD_1IN54_SetWindow(0, 0, EPD_1IN54_WIDTH, EPD_1IN54_HEIGHT);
    for (UWORD j = 0; j < Height; j++) {
        EPD_1IN54_SetCursor(0, j);
        EPD_1IN54_SendCommand(0x24);
        for (UWORD i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_TurnOnDisplay();
}

//���溯��Ϊ������;�ȡģ��ʽ����ʾ����

void EPD_1IN54_Image_Display(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_1IN54_WIDTH % 8 == 0)? (EPD_1IN54_WIDTH / 8 ): (EPD_1IN54_WIDTH / 8 + 1);
    Height = EPD_1IN54_HEIGHT;

    UDOUBLE Addr = 0;
    // UDOUBLE Offset = ImageName;
    EPD_1IN54_SetWindow(0, 0, EPD_1IN54_WIDTH, EPD_1IN54_HEIGHT);
    for (UWORD j = 0; j < Height; j++) {
        EPD_1IN54_SetCursor(0, j);
        EPD_1IN54_SendCommand(0x24);
        for (UWORD i = 0; i < Width; i++) {
            Addr =i + (199-j) * Width;
            EPD_1IN54_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_TurnOnDisplay();
}

/******************************************************************************
function :	 The image of the previous frame must be uploaded, otherwise the
		         first few seconds will display an exception.
parameter:
******************************************************************************/
void EPD_1IN54_DisplayPartBaseImage(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_1IN54_WIDTH % 8 == 0)? (EPD_1IN54_WIDTH / 8 ): (EPD_1IN54_WIDTH / 8 + 1);
    Height = EPD_1IN54_HEIGHT;

    UDOUBLE Addr = 0;
    EPD_1IN54_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_TurnOnDisplayPart();
}


void EPD_1IN54_DisplayPart(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_1IN54_WIDTH % 8 == 0)? (EPD_1IN54_WIDTH / 8 ): (EPD_1IN54_WIDTH / 8 + 1);
    Height = EPD_1IN54_HEIGHT;
	
    UDOUBLE Addr = 0;
    EPD_1IN54_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_TurnOnDisplayPart();
}
/******************************************************************************
���ܣ�����˯��ģʽ
��Χ��
******************************************************************************/
void EPD_1IN54_Sleep(void)
{
    EPD_1IN54_SendCommand(0x10);
    EPD_1IN54_SendData(0x01);
}
