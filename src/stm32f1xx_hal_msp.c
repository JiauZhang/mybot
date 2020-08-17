// SPDX-License-Identifier: BSD 3-Clause license

#include "main.h"

void HAL_MspInit(void)
{
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  // __HAL_AFIO_REMAP_SWJ_DISABLE();
}
