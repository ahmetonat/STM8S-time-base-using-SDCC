
/********************************************************************
 * Copyright 2018 Ahmet Onat
 * This program is distributed under the terms of the 
 * GNU General Public License
 *
 * This file is part of SDCC_TIM1_Tbase
 *
 * SDCC_TIM1_Tbase free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SDCC_TIM1_Tbase is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with SDCC_StmPeriphLib.  If not, see <http://www.gnu.org/licenses/>.
 *
 *********************************************************************/

//This is an example program that implements a 1 millisecond timebase
// using TIM1 overflow interrupt.

// Two methods are demonstrated:
//  A blocking delay call Delayms, and
//  A non-blocking delay wich relies on an external variable set by
//    TIM1 overflow interrupt.

// What is does:
// The on-board LED first blinks using blocking delay 10 times, then
// It blinks using non-blocking timing in a while(1) loop.

#include "stm8s.h"
#include "tim1_tbase.h"

#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOB

void GPIO_Config(void);

// Macros for LED ON-OFF:
#define LED_OFF() GPIO_WriteHigh(LED_PORT, LED_PIN);
#define LED_ON()  GPIO_WriteLow(LED_PORT, LED_PIN);

__IO uint8_t TimerEventFlag; //External variable modified in TIM1 ISR.


void main(void)
{
  int MS_Counter;
  int i;
  

  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);  // select Clock = 16 MHz
  CLK_HSICmd(ENABLE);
  
  GPIO_Config();   // Conigure port for LED signaling on PB5.

  LED_OFF();

  //The following two lines prepare a 1ms timer interrupt.
  TIM1_Config();               // TIM1 configuration
  enableInterrupts();          // Enable interrupts

  MS_Counter=-1;  //Well, the initial value is generally 0 but...

  for (i=0; i<10; ++i){ //Blink LED 20 times using BLOCKING delay.
    LED_ON();
    Delayms(50);       //100ms ON time
    LED_OFF();
    Delayms(50);       //100ms OFF time
  }
  Delayms(500);  //Delayms() implements a blocking timer with argument in ms.

  
  while(1) {
    if (TimerEventFlag==TRUE){ //Here we implement a NON-BLOCKING timing.
      TimerEventFlag=FALSE;    // This variable is set every millisecond by
                               // TIM1 overflow ISR.
      ++MS_Counter;            // It is checked here and counter is incremented.
      if (MS_Counter>1000){
	MS_Counter=0;
      }
    }
    if (MS_Counter==0){
      LED_ON();
    } else if (MS_Counter==100){ // 100ms has passed; LED OFF
      LED_OFF();
    } else if (MS_Counter==200){ // 200ms has passed; LED ON
      LED_ON();
    } else if (MS_Counter==300){ // 300ms has passed; etc.
      LED_OFF();
    }

    // This while(1) loop runs at full speed; it does not wait for the timing.
    // So you can put your own code in here also.
    //  The LED will continue to blink at the same timing pattern.
    //  (unless your code takes longer than 1ms to execute and it misses the
    //   counter increment at the top).

  }//END: while(1)
}  


void GPIO_Config(void) //LED connected to GPIO PB5.
{
  GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_FAST); //GPIO PB5 as output
}



