/* led.c --- 
 * 
 * Filename: led.c
 * Description: Code for the initialization and control of the
        LEDs on the board
 * Author: Thijs Benschop and Jonathan Wegener
 * Created: Thu Sept 19 2013
 * Last-Updated: Thu Sept 26 2013
 *           By: Thijs Benschop
 *     Update #: 1
 * Assignment: Lab4
 *
/* Change log:
 *  added comments to the code for lab 4
 * 
 */

/* Code: */
#include <stm32f30x.h>
#include <f3d_led.h>

void f3d_led_init(void) {
  // initialize the port and pins for the 8 leds
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  //pin 8
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
//pin 9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  //pin 10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  //pin 11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  //pin 12
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  //pin 13
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  //pin 14
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  //pin 15
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  GPIO_Init(GPIOE, &GPIO_InitStructure);
  f3d_led_all_off();
}

void f3d_led_on(int led) {
  // enable the led specified by led parameter
  // led = 0-7 representing the 8 leds
  // 0 is coded to north, with 7 being NW
  switch (led){
  case 0:
    GPIOE->BSRR = GPIO_Pin_9;
    break;
  case 1:
    GPIOE->BSRR = GPIO_Pin_10;
    break;
  case 2:
    GPIOE->BSRR = GPIO_Pin_11;
    break;
  case 3:
    GPIOE->BSRR = GPIO_Pin_12;
    break;
  case 4:
    GPIOE->BSRR = GPIO_Pin_13;
    break;
  case 5:
    GPIOE->BSRR = GPIO_Pin_14;
    break;
  case 6:
    GPIOE->BSRR = GPIO_Pin_15;
    break;
  case 7:
    GPIOE->BSRR = GPIO_Pin_8;
    break;
  }
}
 
void f3d_led_off(int led) {
  // disable the led specified by led parameter
  // led = 0-7 representing the 8 leds
  // 0 is coded to north, with 7 being NW
  switch (led){
  case 0:
    GPIOE->BRR = GPIO_Pin_9;
    break;
  case 1:
    GPIOE->BRR = GPIO_Pin_10;
    break;
  case 2:
    GPIOE->BRR = GPIO_Pin_11;
    break;
  case 3:
    GPIOE->BRR = GPIO_Pin_12;
    break;
  case 4:
    GPIOE->BRR = GPIO_Pin_13;
    break;
  case 5:
    GPIOE->BRR = GPIO_Pin_14;
    break;
  case 6:
    GPIOE->BRR = GPIO_Pin_15;
    break;
  case 7:
    GPIOE->BRR = GPIO_Pin_8;
    break;
  }
} 

void f3d_led_all_on(void) {
  // turn on all 8 leds
  GPIOE->BSRR = GPIO_Pin_8;
  GPIOE->BSRR = GPIO_Pin_9;
  GPIOE->BSRR = GPIO_Pin_10;
  GPIOE->BSRR = GPIO_Pin_11;
  GPIOE->BSRR = GPIO_Pin_12;
  GPIOE->BSRR = GPIO_Pin_13;
  GPIOE->BSRR = GPIO_Pin_14;
  GPIOE->BSRR = GPIO_Pin_15;
} 

void f3d_led_all_off(void) {
  // turn off all 8 leds
  GPIOE->BRR = GPIO_Pin_8;
  GPIOE->BRR = GPIO_Pin_9;
  GPIOE->BRR = GPIO_Pin_10;
  GPIOE->BRR = GPIO_Pin_11;
  GPIOE->BRR = GPIO_Pin_12;
  GPIOE->BRR = GPIO_Pin_13;
  GPIOE->BRR = GPIO_Pin_14;
  GPIOE->BRR = GPIO_Pin_15;
} 

/* led.c ends here */

