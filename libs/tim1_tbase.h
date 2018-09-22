
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

#ifndef _TIM1_TBASE_H_
#define _TIM1_TBASE_H_ //To prevent recursive inclusion.

//TIMER ISR Timebase section start:
//AO! ARR value should be 1000. This is adjusted for the
// internal RC oscillator of the cheap Chinese CPU RC oscillator
// on this particular board:
#define  INIT_TIM1_ARR  943 // 1000  (1MHz/1000=1kHz-> 1ms)
#define  TIM1_PRESCALER 16 //16MHz/1000=1MHz.

#define TIM1_ISRVECT 11

#define TRUE 1
#define FALSE 0

//Timer ISR sets this flag to communicate with the main program.
//Since the variable is used in two files, the header is included in both:
extern __IO uint8_t TimerEventFlag;
// Furthermore, the variable must be defined in one of the two files as:
//__IO uint8_t TimerEventFlag;


static  __IO uint32_t TimingDelay;
void Delayms( uint32_t msTime );

void TIM1_Config(void);
void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void) __interrupt(TIM1_ISRVECT);
//TIMER ISR Timebase section end.


#endif
