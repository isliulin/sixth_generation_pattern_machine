/* Includes ------------------------------------------------------------------*/
#include "includes.h"




/* System IRQ Handler --------------------------------------------------------*/
void NMI_Handler(void)
{
}
void HardFault_Handler(void)
{
  while(1);
}
void MemManage_Handler(void)
{
  
}
void BusFault_Handler(void)
{
  while(1);
}
void UsageFault_Handler(void)
{
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
  SysTickHandler();
}
/* System IRQ Handler --------------------------------------------------------*/