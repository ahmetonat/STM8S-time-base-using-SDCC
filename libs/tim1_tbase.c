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

#include "stm8s.h"

#include "tim1_tbase.h"

void TIM1_Config(void)
{
  TIM1_DeInit();
  // Time base configuration
  TIM1_TimeBaseInit(TIM1_PRESCALER, TIM1_COUNTERMODE_UP, INIT_TIM1_ARR, 0);
  
  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);  // Update Interrupt Enable
  
  TIM1_ARRPreloadConfig(ENABLE);          // ARRPreload Enable
  
  TIM1_Cmd(ENABLE);                       // Enable TIM1
}

//INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void) __interrupt(TIM1_ISRVECT)
{

  TimerEventFlag = TRUE; // This variable is exported to be used in main.c

  if (TimingDelay != 0x00){  // Delayms function counter.
    TimingDelay --;
  }
 
  TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
}


void Delayms( uint32_t msTime ){
  //Blocking delay timer. 
  //Depends on the TIM1 overflow handler.
  TimingDelay = msTime ;
  while (TimingDelay != 0);   //Burn off time while the timer ISR occurs.
}


