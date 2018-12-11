//XMC Lib Project includes:
#include "CAN0.h"


void CAN0_Init(void)
{
  XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_baud;
  
  /*Configure CAN Module*/
  XMC_CAN_Init(CAN,SystemCoreClock);
  
  /*Configure CAN Node baudrate*/
  CAN_baud.can_frequency = SystemCoreClock;
  CAN_baud.baudrate = 50000;
  CAN_baud.sample_point = 8000;
  CAN_baud.sjw = 1;
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE0, &CAN_baud);
  
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE0);
  XMC_CAN_NODE_SetInitBit(CAN_NODE0);
}
void CAN0_0_IRQHandler(void)
{
  
}
void CAN0_1_IRQHandler(void)
{
  
}
void CAN0_2_IRQHandler(void)
{
  
}
void CAN0_3_IRQHandler(void)
{
  
}

