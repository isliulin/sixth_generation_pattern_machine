//XMC Lib Project includes:
#include "CAN1.h"


#define CAN1_0_IRQHandler       CAN0_4_IRQHandler
#define CAN1_1_IRQHandler       CAN0_5_IRQHandler
#define CAN1_2_IRQHandler       CAN0_6_IRQHandler
#define CAN1_3_IRQHandler       CAN0_7_IRQHandler



void CAN1_Init(void)
{
  XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_baud;
  
  /*Configure CAN Module*/
  XMC_CAN_Init(CAN,SystemCoreClock);
  
  /*Configure CAN Node baudrate*/
  CAN_baud.can_frequency = SystemCoreClock;
  CAN_baud.baudrate = 50000;
  CAN_baud.sample_point = 8000;
  CAN_baud.sjw = 1;
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE1, &CAN_baud);
}


void CAN1_4_IRQHandler(void)
{
  
}
void CAN1_5_IRQHandler(void)
{
  
}
void CAN1_6_IRQHandler(void)
{
  
}
void CAN1_7_IRQHandler(void)
{
  
}