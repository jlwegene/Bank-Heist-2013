#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_lcd_sd.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_delay.h>
#include <f3d_mag.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <menu.h>

void menuMain(){
	f3d_lcd_fillScreen(BLACK);
	f3d_lcd_drawString(20,20,"BANK HEIST 2013",RED,BLACK);
	f3d_lcd_drawString(30,40,"Play",WHITE,BLACK);
	f3d_lcd_drawString(30,60,"High Scores",WHITE,BLACK);
	f3d_lcd_drawString(30,80,"Settings",WHITE,BLACK);
}

void updateSelect(int* skips, int* selected, nunchuk_t* nData){
	if(*skips>=12){
      if((*nData).jy>254){
          *selected=*selected-1;
          if(*selected<0) *selected = 2;
       }
      else if((*nData).jy<1){
          *selected=*selected+1;
          if(*selected==3) *selected=0;
      }
      *skips=0;
    }
    else
   	  *skips=(*skips)+1;

  switch(*selected){
  	 case 0:
        drawTriangle(26,44,BLUE);
        drawTriangle(26,64,BLACK);
        drawTriangle(26,84,BLACK);
        break;
      case 1:
        drawTriangle(26,44,BLACK);
        drawTriangle(26,64,BLUE);
        drawTriangle(26,84,BLACK);
        break;
      case 2:
        drawTriangle(26,44,BLACK);
        drawTriangle(26,64,BLACK);
        drawTriangle(26,84,BLUE);
        break;
  }
}

void drawTriangle(int xpos, int ypos, uint16_t color) {
  int i,j;
  int s_py = ypos;
  int r_size = 1;
  for(i=0;i<=5;i++){
    for(j=0;j<r_size;j++){
      f3d_lcd_drawPixel(xpos-i, j+s_py, color);
    }
    r_size+=2;
    s_py-=1;
  }
}

void drawGrid(){
	int i,j;
	for(i = -1; i < 128; i+=16){
		for(j = 0; j < 160; j+=1){
			f3d_lcd_drawPixel(i,j,WHITE);
		}
	}
	for(i = -1; i < 160; i+=16){
		f3d_lcd_drawLine(0,i,127,i,WHITE);
	}
}