#include <msp430fr5994.h>
#include "driverlib.h"
#include "lcd.h"
#include "lcd_definitions.h"
#include "lcdspi.h"

void LCD_Clear(void);
void goHome(void);
void lcdRow(unsigned char r);
void lcdCol(unsigned char c);
void LCD_PrintString( char* s);
void gotoXy(unsigned char , unsigned char);
void LCD_PrintCharacter(unsigned char r);

void write_buffer(unsigned char* buffer);
void LCD_SendData(unsigned char data);
void LCD_SendCommand(unsigned char cmd);

int send_command = 1;
int send_data = 0;

void LCD_Init(){
     LCDSPI_Init(send_command);
     P2DIR = BIT4;
     P5DIR = BIT5;
     RSTPORT &= ~RST;
     __delay_cycles(1000);
     RSTPORT |= RST;


       A0PORT &=~A0;
       LCDSPI_Transmit(CMD_SET_BIAS_7);

       LCDSPI_Transmit(CMD_SET_ADC_NORMAL);
       LCDSPI_Transmit(CMD_SET_COM_NORMAL);
       LCDSPI_Transmit(CMD_SET_DISP_START_LINE);


       LCDSPI_Transmit(CMD_SET_POWER_CONTROL | 0x4 );
        __delay_cycles(1000);
       LCDSPI_Transmit(CMD_SET_POWER_CONTROL | 0x7);

        __delay_cycles(1000);


       LCDSPI_Transmit(CMD_DISPLAY_ON);


       LCDSPI_Transmit(CMD_SET_ALLPTS_NORMAL);

       LCD_Clear();

}

void LCD_Display(char *s, int x, int y){
    LCD_Clear();
    gotoXy(x,y);
    LCD_PrintString(s);
}


void LCD_Clear(void){
    unsigned char i, j;

    for(i = 0; i < 8; i++) {

        LCD_SendCommand(0xB0 | i); //sets page(row) from 0 to 7
        LCD_SendCommand(0x10);             //sets column address(MSB) to 0 for each page(row)
        LCD_SendCommand(0x00);             //sets Column address(LSB)to 0 for each page(row)

        for(j = 0; j < 132; j++) {
            LCD_SendData(0x00);
        }

    }
}




void LCD_PrintCharacter(unsigned char r)
{
    char i;
    for ( i = 0; i < 6; i++ ){
        LCD_SendData(font6x8[r - 32][i] );
    }

    //LCDSPI_Transmit(LCD_DATA | 0); // 1px gap after each letter

}


void LCD_SendData(unsigned char data)
{
    A0PORT |=A0;
    LCDSPI_Init(send_data);
    LCDSPI_Transmit(data);
}

void LCD_SendCommand(unsigned char cmd)
{
    A0PORT &=~A0;
    LCDSPI_Init(send_command);
    LCDSPI_Transmit(cmd);
}
/*
void printnummega(unsigned char x, unsigned char y,unsigned char n)
{
    unsigned char i;
    gotoXy(x,y);
    for(i=0;i<15;i++)
    {
        LCD_SendData(nummega[n][0][i] );
    }
    gotoXy(x+1,y);
    for(i=0;i<15;i++)
    {
        LCD_SendData(nummega[n][1][i] );
    }
    gotoXy(x+2,y);
    for(i=0;i<15;i++)
    {
        LCD_SendData(nummega[n][2][i] );
    }
}*/


void write_buffer(unsigned char *buffer) {
  unsigned char c, p;

  for(p = 0; p < 8; p++) {
    gotoXy(p,0); //row , column
    for(c = 0; c < 132; c++) {
     LCD_SendData(buffer[(128*p)+c]);
    }
  }

}


void setpixel(unsigned char *buff, unsigned char x, unsigned char y) {
     buff[((y/8)*128)+x] |=  0x01<<(y%8);
}


// the most basic function, clear a single pixel
void clearpixel(unsigned char *buff, unsigned char x, unsigned char y) {
  // x is which column
  buff[x+ (y/8)*128] &= ~(0x01<<(y%8));
}

/*/ bresenham's algorithm - thx wikpedia
void drawline(unsigned char *buff,unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) {
 unsigned char temp;
  unsigned char steep = (y1 - y0) > (x1 - x0);
  if (steep) {
    temp=x0;
    x0 = y0;
    y0 = temp;
    temp=x1;
    x1 = y1;
    y1 = temp;
  }
  if (x0 > x1) {
     temp=x0;
    x0 = x1;
    x1 = temp;
     temp=y0;
    y0 = y1;
    y1 = temp;
;
  }
  unsigned char dx, dy;
  dx = x1 - x0;
  dy = (y1 - y0);
   char err = dx / 2;
   char ystep;
  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}
  for (; x0<x1; x0++) {
    if (steep) {
      setpixel(buff, y0, x0);
    } else {
      setpixel(buff, x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}*/

// filled rectangle
void fillrect(unsigned char *buff,unsigned char x, unsigned char y, unsigned char w, unsigned char h) {
unsigned char i,j;
  // stupidest version - just pixels - but fast with internal buffer!
  for (i=x; i<x+w; i++) {
    for ( j=y; j<y+h; j++) {
      setpixel(buff, i, j);
    }
  }
}


// draw a rectangle
void drawrect(unsigned char *buff,unsigned char x, unsigned char y, unsigned char w, unsigned char h) {
unsigned char i;
  // stupidest version - just pixels - but fast with internal buffer!

  for ( i=x; i<x+w; i++) {
    setpixel(buff, i, y);
    setpixel(buff, i, y+h-1);
  }


  for ( i=y; i<y+h; i++) {
    setpixel(buff, x, i);
    setpixel(buff, x+w-1, i);
  }

}

/*
// draw a circle
void drawcircle(unsigned char *buff,unsigned char x0, unsigned char y0, unsigned char r ) {
  char f = 1 - r;
  char ddF_x = 1;
  char ddF_y = -2 * r;
  char x = 0;
  char y = r;
  setpixel(buff, x0, y0+r);
  setpixel(buff, x0, y0-r);
  setpixel(buff, x0+r, y0);
  setpixel(buff, x0-r, y0);
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    setpixel(buff, x0 + x, y0 + y);
    setpixel(buff, x0 - x, y0 + y);
    setpixel(buff, x0 + x, y0 - y);
    setpixel(buff, x0 - x, y0 - y);
    setpixel(buff, x0 + y, y0 + x);
    setpixel(buff, x0 - y, y0 + x);
    setpixel(buff, x0 + y, y0 - x);
    setpixel(buff, x0 - y, y0 - x);
  }
}*/


/*/ draw a circle
void fillcircle(unsigned char *buff,
          unsigned char x0, unsigned char y0, unsigned char r,
          unsigned char color) {
 char f = 1 - r;
 char ddF_x = 1;
  char ddF_y = -2 * r;
  char x = 0;
  char y = r;
unsigned char i;
  for (i=y0-r; i<=y0+r; i++) {
    setpixel(buff, x0, i);
  }
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    for (i=y0-y; i<=y0+y; i++) {
      setpixel(buff, x0+x, i);
      setpixel(buff, x0-x, i);
    }
    for ( i=y0-x; i<=y0+x; i++) {
      setpixel(buff, x0+y, i);
      setpixel(buff, x0-y, i);
    }
  }
}*/


// clear everything
void clearBuffer(unsigned char *buff) {


    unsigned int i;

    for (i=0;i<1056;i++)
    {
        buff[i]= 0x00;
    }
}

void goHome(void)
{
    LCD_SendCommand(0xB0);  //sets page(row) to 0
    LCD_SendCommand(0x10);  //sets column to 0
    LCD_SendCommand(0x00);
}

void lcdRow(unsigned char r)
{
    LCD_SendCommand(0xB0 | (r & 0x0F));
}

void lcdCol(unsigned char c)
{   LCD_SendCommand(0x10 | (c>>4)); // Sets the DDRAM column addr - upper 3-bit
    LCDSPI_Transmit(0x00 | (c & 0x0F)); // lower 4-bit
}

// gotoXy(Row , column ) , row-> max 8 , column->95
void gotoXy(unsigned char x,unsigned char y)
{
    switch(x){
    case 0: x = 3;
            break;
    case 1: x = 2;
            break;
    case 2: x = 1;
            break;
    case 3: x = 0;
            break;
    case 4: x = 7;
            break;
    case 5: x = 6;
            break;
    case 6: x = 5;
            break;
    case 7: x = 4;
            break;
    }

    LCD_SendCommand(0xB0|(x & 0x0F));

    LCD_SendCommand(0x10|((y>>4)));
    LCD_SendCommand(0x00|(y & 0x0F));
}

void LCD_PrintString(char* s)
{

    while(*s)
    {
        LCD_PrintCharacter(*s++);
    }
}

