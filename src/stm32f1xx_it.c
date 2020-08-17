// SPDX-License-Identifier: BSD 3-Clause license

#include "main.h"
#include "stm32f1xx_it.h"

void NMI_Handler(void)
{
  HAL_RCC_NMI_IRQHandler();
}

void HardFault_Handler(void)
{
  while (1)
  {

  }
}


void MemManage_Handler(void)
{
  while (1)
  {

  }
}

void BusFault_Handler(void)
{
  while (1)
  {

  }
}

void UsageFault_Handler(void)
{
  while (1)
  {

  }
}

void SVC_Handler(void)
{
	
}

void DebugMon_Handler(void)
{
	
}

void PendSV_Handler(void)
{
	
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}