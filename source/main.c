/* main.c 
 * 
 * Filename: main.c
 * Description: lab 8 code for gyro output on lcd
 * Author: Thijs Benschop and Jonathan Wegener
 * Created: Thu Oct 24 2013
 * Last-Updated: Thu Oct 31 2013
 *           By: Thijs Benschop and Jonathan Wegener
 *     Update #: 1
 * 
 */

/* Change log:
 * added all of the display code and gyro data interpretation code and comments
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_i2c.h>
#include <f3d_uart.h>
#include <f3d_rtc.h>
#include <stdio.h>
#include <f3d_delay.h>
#include <f3d_systick.h>
#include <f3d_lcd_sd.h>
#include <stdlib.h>
#include <structures.h>
#include <player.h>
#include <menu.h>
#include <settings.h>
#include <level.h>
#include <block.h>
#include <scores.h>
#include <f3d_accel.h>
#include <math.h>
#include <ff.h>
#include <f3d_dac.h>
#include <f3d_timer2.h>
#include <audioPlayer.h>
#include <movingBlock.h>


FATFS Fatfs;
player p1,p2;
scores hiScores;
options option;
nunchuk_t pone, ptwo;
level* currentLevel;
int screen = 0, lastscreen = 0;
int menuDelay = 0, menuSelected = 0;
int settingsSelected = 0, settingsDelay = 0, optionSkip = 0;
int curLvlNum = 0, resetFlag = 1, scoresRead = 0;

void pitch_roll(float* res);

int main(void) { 
  //initialize all the peripherals
  f3d_delay_init();
  f3d_i2c1_init();
  f3d_accel_init();
  f3d_i2c2_init();
  f3d_rtc_init();
  f3d_timer2_init();
  //f3d_dac_init();
  f3d_lcd_init();
  f3d_uart_init();
  f3d_led_init();
  f3d_nunchuk_init();
  f3d_systick_init();

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  level levelOne, levelTwo, levelThree;
  // 

  f_mount(0, &Fatfs);
  menuMain();
  p1 = initP1();
  p2 = initP2();
  initScores(&hiScores);
  initOptions(&option);
  // initLevel1(&p1,&p2, &levelOne);
  // resetLevel1(&p1,&p2, &levelOne);
  initLevel1(&p1,&p2, &levelOne);
  initLevel2(&p1,&p2, &levelTwo);
  initLevel3(&p1,&p2, &levelThree);
  currentLevel = &levelThree;
  // initLevel3(&p1,&p2, &levelThree);
  // currentLevel = &levelThree;
  curLvlNum = 3; 

  while(1){
    f3d_delay_uS(200);
    switch(screen){
      case 0:
      if(lastscreen!=screen){
        menuMain();
        lastscreen=screen;
      }
        updateSelect(&menuDelay,&menuSelected,&pone);
        break;
      case 1:
        if(lastscreen!=screen){
          drawLevel(*currentLevel);
          drawPlayer(p1);
          drawPlayer(p2);
          lastscreen=screen;
        }
        break;
      case 2:
        if(lastscreen!=screen){
          displayScores(&hiScores,scoresRead);
          scoresRead=1;
          lastscreen=screen;
        }
        break;
      case 3:
        if(lastscreen!=screen){
          settingsMain(option);
          lastscreen = screen;
        }
        updateSettingsSelect(&settingsDelay,&settingsSelected,&pone);
        break;
      default:
        printf("Sad face\n");
        break;
    }
    if((*currentLevel).blocksLeft <= 0){
      if(curLvlNum == 1){
        resetLevel2(&p1,&p2, &levelTwo);
        currentLevel = &levelTwo;
        curLvlNum = 2;
        drawLevel(*currentLevel);
        drawPlayer(p1);
        drawPlayer(p2);
      }else if(curLvlNum == 2){
        // playFile("chaching.wav");
        resetLevel3(&p1,&p2, &levelThree);
        currentLevel = &levelThree;
        curLvlNum = 3;
        drawLevel(*currentLevel);
        drawPlayer(p1);
        drawPlayer(p2);
      }else{
        currentLevel = &levelOne;
        resetLevel1(&p1, &p2,currentLevel);
        lastscreen = screen;
        screen = 0;
        menuMain();
      }
    }
    
  }
  while(1);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
  printf("failed assert in line %d \n", line);
  // f3d_uart_init();

/* Use GDB to find out why we're here */
  //printf("Assertion raised at line %d in file %s\n",line,file);
  while (1);
}
#endif

int getDirection(nunchuk_t nData)
{
  if(nData.jy>=254)
    return UP;
  else if(nData.jy<=1)
    return DOWN;
  else if(nData.jx>=254)
    return RIGHT;
  else if(nData.jx<=1)
    return LEFT;
  else
    return STAND;
}

void SysTick_Handler(void) {
  static int counter = 0;
  static int ledpos = 0;
  if(screen==1||screen==0||screen==3){
    f3d_nunchuk_read(&pone);
    f3d_nunchuk_read2(&ptwo);
  }
  if(screen==1){
    int dpone = getDirection(pone);
    int dptwo = getDirection(ptwo);
    if(dpone) movePlayer(&p1, &p2, dpone,currentLevel, &option);
    if(dptwo) movePlayer(&p2, &p1, dptwo,currentLevel, &option);
    if(pone.c || ptwo.c && !resetFlag){
      resetFlag = 1;
      if(curLvlNum == 1){
        resetLevel1(&p1, &p2,currentLevel);
        drawLevel(*currentLevel);
        drawPlayer(p1);
        drawPlayer(p2);
      }else if(curLvlNum == 2){
        resetLevel2(&p1, &p2,currentLevel);
        drawLevel(*currentLevel);
        drawPlayer(p1);
        drawPlayer(p2);
      }else if(curLvlNum == 3){
        resetLevel3(&p1, &p2,currentLevel);
        drawLevel(*currentLevel);
        drawPlayer(p1);
        drawPlayer(p2);
      }
      resetFlag = 0;
    }
    if(curLvlNum == 3){
      float pr[3];
      pitch_roll(pr);
      float pitch = pr[0];
      float roll = pr[1];
      if(roll<=-20){
        moveMovingBlock(RIGHT, currentLevel,&p1, &p2);
      }
      else if(roll>=20){
        moveMovingBlock(LEFT, currentLevel,&p1, &p2);
      }
    }
  }
  else if(screen==0){
    if(pone.z||pone.c)
      screen = menuSelected+1;
  }
  else if(screen == 3){
    //if(counter%6==0){
      if(pone.z||pone.c){
        int garbage = changeOption(&optionSkip,&settingsSelected,&option);
      }
    //}
  }

  int bstate = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);

  if(bstate){
    lastscreen = screen;
    screen = 0;
  }

  if((bstate && (counter >= 10)) || !bstate){
    if(option.leds){
      f3d_led_off(ledpos);
      ++ledpos;
      ledpos = ledpos % 8;
      f3d_led_on(ledpos);
    }
    counter = 0;
  }else{
    counter++;
  }

  
  check_flush();
}


void pitch_roll(float* res)
{
  float a_data[3], PI = 3.1415;
  f3d_accel_read(a_data);
  float pitch = atan(a_data[0]/sqrt(pow(a_data[1],2)+pow(a_data[2],2)));
  float roll = atan(a_data[1]/sqrt(pow(a_data[0],2)+pow(a_data[2],2)));
  res[0]=(pitch*180)/(PI);
  res[1]=(roll*180)/(PI);
}
/* main.c ends here */
