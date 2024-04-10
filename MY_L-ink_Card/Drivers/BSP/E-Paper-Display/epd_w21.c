#include "epd_w21_config.h"
#include "stm32l0xx_hal.h"
#include "DEV_Config.h"


void DriverDelay(unsigned long xms)
{
    HAL_Delay(xms);
}


void SpiWrite(unsigned char value)
{
    unsigned char i;
    
    SpiDelay(1);
    for (i = 0; i < 8; i++)
    {
        EPD_W21_CLK_0;
        SpiDelay(1);
        if (value & 0x80)
            EPD_W21_MOSI_1;
        else
            EPD_W21_MOSI_0;
        value = (value << 1);
        SpiDelay(1);
        EPD_W21_CLK_1;
        SpiDelay(1);
    }
}

static unsigned char ReadBusy(void)
{
    unsigned long i = 0;


    for (i = 0; i < 400; i++)
    {
        if (isEPD_W21_BUSY == EPD_W21_BUSY_LEVEL)
        {
            return 1;
        }
        DriverDelay(10);
    }
    return 0;
}

static void EpdW21WriteCMD(unsigned char command)
{
    EPD_W21_CS_0;
    EPD_W21_DC_0;        // command write
    SpiWrite(command);
    EPD_W21_CS_1;
}

static void EpdW21WriteCMD_p1(unsigned char command, unsigned char para)
{
    //while(isEPD_W21_BUSY == 1);	// wait
    ReadBusy();

    EPD_W21_CS_0;
    EPD_W21_DC_0;        // command write
    SpiWrite(command);
    EPD_W21_DC_1;        // command write
    SpiWrite(para);
    EPD_W21_CS_1;
}

static void EpdW21Write(unsigned char *value, unsigned char datalen)
{
    unsigned char i = 0;
    unsigned char *ptemp;

    ptemp = value;

    EPD_W21_CS_0;
    EPD_W21_DC_0;        // command write

    SpiWrite(*ptemp);
    ptemp++;

    EPD_W21_DC_1;        // data write

    for (i = 0; i < datalen - 1; i++)    // sub the command
    {
        SpiWrite(*ptemp);
        ptemp++;
    }

    EPD_W21_CS_1;

}

void EPD_W21_WriteDATA(unsigned char command)
{
    SpiDelay(1);
    EPD_W21_CS_0;                   
	EPD_W21_DC_1;		// command write
	SpiWrite(command);
	EPD_W21_CS_1;
}

static void EpdW21WriteDispRam(unsigned char XSize, unsigned int YSize,
                               unsigned char *Dispbuff)
{
    int i = 0, j = 0;

    if (XSize % 8 != 0)
    {
        XSize = XSize + (8 - XSize % 8);
    }
    XSize = XSize / 8;

    while(isEPD_W21_BUSY == 1);	//wait
    ReadBusy();

    EPD_W21_CS_0;
    EPD_W21_DC_0;        //command write
    SpiWrite(0x24);

    EPD_W21_DC_1;        //data write
    for (i = 0; i < YSize; i++)
    {
        for (j = 0; j < XSize; j++)
        {
            SpiWrite(*Dispbuff);
            Dispbuff++;
        }
    }

    EPD_W21_CS_1;
}

static void EpdW21WriteDispRamMono(unsigned char XSize, unsigned int YSize,
                                   unsigned char dispdata)
{
    int i = 0, j = 0;

    if (XSize % 8 != 0)
    {
        XSize = XSize + (8 - XSize % 8);
    }
    XSize = XSize / 8;
    //while(isEPD_W21_BUSY == 1);	// wait
    ReadBusy();

    EPD_W21_CS_0;
    EPD_W21_DC_0;        // command write
    SpiWrite(0x24);

    EPD_W21_DC_1;        // data write
    for (i = 0; i < YSize; i++)
    {
        for (j = 0; j < XSize; j++)
        {
            SpiWrite(dispdata);
        }
    }

    EPD_W21_CS_1;
}

static void EpdW21DispInit(void)
{
	EpdW21WriteCMD(0x12);
	while(isEPD_W21_BUSY == 1) DriverDelay(10);	//wait
//    EpdW21Write(GDOControl, sizeof(GDOControl));    // Pannel configuration, Gate selection
    EpdW21Write(softStart, sizeof(softStart));    // X decrease, Y decrease
    EpdW21Write(dummyLine, sizeof(dummyLine));    // dummy line per gate
    EpdW21Write(gateTime, sizeof(gateTime));        // Gage time setting
    EpdW21Write(ramDataEntryMode, sizeof(ramDataEntryMode));    // X increase, Y decrease
    EpdW21Write(border, sizeof(border));  
    EpdW21Write(rbits, sizeof(rbits));  
	EpdW21Write(loadtemp, sizeof(loadtemp));
	EpdW21WriteCMD(0x20);
	EpdW21Write(setx, sizeof(setx));  
	EpdW21Write(sety, sizeof(sety));  
//    EpdW21WriteCMD(0x2c);
//    EpdW21Write(VCOMVol,sizeof(VCOMVol));
    
	while(isEPD_W21_BUSY == 1) DriverDelay(10);	//wait
}

static void EpdW21Init(void)
{
	
    EPD_W21_DC_0;
	EPD_W21_CS_0;
    EPD_W21_RST_1;
    DriverDelay(200);  
	EPD_W21_RST_0;        // Module reset
    DriverDelay(10);
    EPD_W21_RST_1;
    DriverDelay(200);
	while(isEPD_W21_BUSY == 1) DriverDelay(10);	//wait
	

    EpdW21DispInit();        // pannel configure
}

static void EpdW21Update(void)
{
    EpdW21WriteCMD_p1(0x22, 0xf7);
    EpdW21WriteCMD(0x20);
}

void EpdInitFull(void)
{
    EpdW21Init();     
}

void EpdDisFull(unsigned char *DisBuffer, unsigned char Label)
{
    if (Label == 0)
    {
        EpdW21WriteDispRamMono(xDot, yDot, 0x00);    // white
    } 
    else
    {
        EpdW21WriteDispRam(xDot, yDot, (unsigned char *) DisBuffer);    // white
    }
    EpdW21Update();

}
