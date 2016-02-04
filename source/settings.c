#include <f3d_lcd_sd.h>
#include <structures.h>
#include <settings.h>
#include <stdio.h>

void settingsMain(options op){
	f3d_lcd_fillScreen(BLACK);
	f3d_lcd_drawString(30,10,"Settings",RED,BLACK);
	f3d_lcd_drawString(15,40,"Sounds",WHITE,BLACK);
	f3d_lcd_drawString(15,60,"Entropy",WHITE,BLACK);
	f3d_lcd_drawString(15,80,"Instructions",WHITE,BLACK);
	f3d_lcd_drawString(15,100,"LEDs",WHITE,BLACK);
	settingsToggles(&op,0);
	settingsToggles(&op,1);
	settingsToggles(&op,2);
	settingsToggles(&op,3);
}

void settingsToggles(options* op, int c){
	switch(c){
		case 0: drawIndicator(100,40,(*op).music); break;
		case 1:	drawIndicator(100,60,(*op).dicks); break;
		case 2:	drawIndicator(100,80,(*op).instructions); break;
		case 3:	drawIndicator(100,100,(*op).leds); break;
	}	
}

void drawIndicator(int x, int y, int onoff){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(onoff){
				f3d_lcd_drawPixel(x+i,y+j,GREEN);
			}
			else
				f3d_lcd_drawPixel(x+i,y+j,RED);
		}
	}
}

void initOptions(options* o){
	(*o).music = 1;
	(*o).dicks = 0;
	(*o).instructions = 0;
	(*o).leds = 1;
}

void updateSettingsSelect(int * skips, int* selected, nunchuk_t* nData){
    if(*skips>=12){
      if((*nData).jy>254){
          *selected=*selected-1;
          if(*selected<0) *selected = 3;
       }
      else if((*nData).jy<1){
          *selected=*selected+1;
          if(*selected==4) *selected=0;
      }
      *skips=0;
    }
    else
   	  *skips=(*skips)+1;

  switch(*selected){
  	 case 0:
        drawTriangle(11,44,BLUE);
        drawTriangle(11,64,BLACK);
        drawTriangle(11,84,BLACK);
        drawTriangle(11,104,BLACK);
        break;
      case 1:
        drawTriangle(11,44,BLACK);
        drawTriangle(11,64,BLUE);
        drawTriangle(11,84,BLACK);
        drawTriangle(11,104,BLACK);
        break;
      case 2:
        drawTriangle(11,44,BLACK);
        drawTriangle(11,64,BLACK);
        drawTriangle(11,84,BLUE);
        drawTriangle(11,104,BLACK);
        break;
      case 3:
        drawTriangle(11,44,BLACK);
        drawTriangle(11,64,BLACK);
        drawTriangle(11,84,BLACK);
        drawTriangle(11,104,BLUE);
        break;
  }

}

int changeOption(int* skips, int* selected, options* op){
	if(*skips<3){
		*skips = *skips+1;
		return 1;
	}
	*skips = 0;
	int changed = 0;
	//printf("changeOption s = %d \n",(*selected));
	switch(*selected){
		case 0:
			(*op).music = (*op).music ^ 1; changed = 0; break;
		case 1:
			(*op).dicks = (*op).dicks ^ 1; changed = 1; break;
		case 2:
			(*op).instructions = (*op).instructions ^ 1; changed = 2; break;
		case 3:
			(*op).leds = (*op).leds ^ 1; changed = 3; break;
	}
	settingsToggles(op,changed);
	return 1;
}

