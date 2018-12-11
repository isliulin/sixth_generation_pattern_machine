/*********************************************************************************************************************
* Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
*
* Infineon Technologies AG (Infineon) is supplying this software for use with Infineon's microcontrollers.
* This file can be freely distributed within development tools that are supporting such microcontrollers.
*
* THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
* 
* INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,OR CONSEQUENTIAL DAMAGES, FOR ANY REASON
* WHATSOEVER.
*
* @file        CCU80.c 
* @date        Nov 18, 2015
* @version     1.0.0
*
* @brief       CCU80 initialization function based on LLD
*
* APIs provided in this file cover the following functional blocks : <br>
*
* - CCU80_Init()
*
* History <br>
* Version 0.1.0    Initial <br>
*
********************************************************************************************************************/

/*********************************************************************************************************************
* HEADER FILES
********************************************************************************************************************/
#include "CCU80.h"
#include "xmc_gpio.h"

/*********************************************************************************************************************
* MACROS
********************************************************************************************************************/
#define MODULE_PTR      	CCU80

#define SLICE0_PTR       	CCU80_CC80
#define SLICE0_NUMBER    	(0U)

#define SLICE1_PTR       	CCU80_CC81
#define SLICE1_NUMBER    	(1U)

/*********************************************************************************************************************
* ENUMS
********************************************************************************************************************/

/*********************************************************************************************************************
* DATA STRUCTURES
********************************************************************************************************************/

/*********************************************************************************************************************
* LOCAL DATA
********************************************************************************************************************/
static const XMC_CCU8_SLICE_COMPARE_CONFIG_t CCU80_slide_config =
{
  .timer_mode 		   = (uint32_t) XMC_CCU8_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot   		   = (uint32_t) false,
  .shadow_xfer_clear   = (uint32_t) 0U,
  .dither_timer_period = (uint32_t) 0U,
  .dither_duty_cycle   = (uint32_t) 0U,
  
  .mcm_ch1_enable 	   = (uint32_t) false,
  .mcm_ch2_enable 	   = (uint32_t) false,
  
  .slice_status 	   = (uint32_t) XMC_CCU8_SLICE_STATUS_CHANNEL_1,
  
  .prescaler_mode	   = (uint32_t) XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL,
  
  
  .passive_level_out0  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out1  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out2  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out3  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  
  .asymmetric_pwm	   = (uint32_t) 1U,
  
  .invert_out0	   	   = (uint32_t) 0U,
  .invert_out1	   	   = (uint32_t) 1U,
  .invert_out2	   	   = (uint32_t) 0U,
  .invert_out3	   	   = (uint32_t) 1U,
  
  .prescaler_initval   = (uint32_t) 5U, // 144/32 = 4.5M
  .float_limit		   = (uint32_t) 0U,
  .dither_limit		   = (uint32_t) 0U,
  .timer_concatenation = (uint32_t) 0U
};

static const XMC_CCU8_SLICE_EVENT_CONFIG_t START_config =
{
  .mapped_input = XMC_CCU8_SLICE_INPUT_H, // SCU.GLCCST80
  .edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE, // Rising edge for start
  .level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_LOW, // Low level active for modulation
  .duration = XMC_CCU8_SLICE_EVENT_FILTER_7_CYCLES
};

uint16_t Slice0_Period, Slice1_Period, Slice0_Compare0, Slice0_Compare1, Slice1_Compare0, Slice1_Compare1;

/*********************************************************************************************************************
* GLOBAL DATA
********************************************************************************************************************/

/*********************************************************************************************************************
* LOCAL ROUTINES DEFINITION
********************************************************************************************************************/

/*********************************************************************************************************************
* GLOBAL ROUTINES DEFINITION
********************************************************************************************************************/

/*********************************************************************************************************
void CCU80_Init(uint32_t Period_Value, uint32_t DeadTime_Value
**********************************************************************************************************/
void CCU80_Init(void)
{
  Slice0_Period = 60000;
  Slice0_Compare0 = 10000;
  Slice0_Compare1 = 40000;
  
  Slice1_Period = 60000;
  Slice1_Compare0 = 25000;
  Slice1_Compare1 = 55000;
  
  //	XMC_SCU_CLOCK_EnableClock(SCU_CLK_CLKCLR_CCUCDI_Msk);
  
  /* Enable clock, enable prescaler block and configure global control */
  XMC_CCU8_Init(MODULE_PTR, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
  
  /* Start the prescaler and restore clocks to slices */
  XMC_CCU8_StartPrescaler(MODULE_PTR);
  
  /* Start of CCU8 configurations */
  /* Ensure fCCU reaches CCU80 */
  XMC_CCU8_SetModuleClock(MODULE_PTR, XMC_CCU8_CLOCK_SCU);
  
  /**********************************************************************/
  /*                   CC80 configuration                               */
  /**********************************************************************/
  /* Configure CCU8x_CC8y slice as timer */
  XMC_CCU8_SLICE_CompareInit(SLICE0_PTR, &CCU80_slide_config);
  
  /* Set period match value of the timer  */
  XMC_CCU8_SLICE_SetTimerPeriodMatch(SLICE0_PTR, Slice0_Period - 1);
  /* Set timer compare match value for channel 1 */
  XMC_CCU8_SLICE_SetTimerCompareMatch(SLICE0_PTR, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, Slice0_Compare0 - 1);
  /* Set timer compare match value for channel 2 */
  XMC_CCU8_SLICE_SetTimerCompareMatch(SLICE0_PTR, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, Slice0_Compare1 - 1);
  
  /* Transfer value from shadow timer registers to actual timer registers */
  XMC_CCU8_EnableShadowTransfer(MODULE_PTR, XMC_CCU8_SHADOW_TRANSFER_SLICE_0 | XMC_CCU8_SHADOW_TRANSFER_PRESCALER_SLICE_0);
  
  /* Configure start event */
  /* Configure event 0 */
  XMC_CCU8_SLICE_ConfigureEvent(SLICE0_PTR, XMC_CCU8_SLICE_EVENT_0, &START_config);
  XMC_CCU8_SLICE_StartConfig(SLICE0_PTR, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START_CLEAR);
  
  /* Get the slice out of idle mode */
  XMC_CCU8_EnableClock(MODULE_PTR, SLICE0_NUMBER);
  
  
  // CCU80 PWM IOs Settings
  XMC_GPIO_SetMode(P0_5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);   // CCU80.OUT00
  
  /**********************************************************************/
  /*                   CC81 configuration                               */
  /**********************************************************************/
  /* Configure CCU8x_CC8y slice as timer */
  XMC_CCU8_SLICE_CompareInit(SLICE1_PTR, &CCU80_slide_config);
  
  /* Set period match value of the timer  */
  XMC_CCU8_SLICE_SetTimerPeriodMatch(SLICE1_PTR, Slice1_Period - 1);
  /* Set timer compare match value for channel 1 */
  XMC_CCU8_SLICE_SetTimerCompareMatch(SLICE1_PTR, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, Slice1_Compare0 - 1);
  /* Set timer compare match value for channel 2 */
  XMC_CCU8_SLICE_SetTimerCompareMatch(SLICE1_PTR, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, Slice1_Compare1 - 1);
  
  /* Transfer value from shadow timer registers to actual timer registers */
  XMC_CCU8_EnableShadowTransfer(MODULE_PTR, XMC_CCU8_SHADOW_TRANSFER_SLICE_1 | XMC_CCU8_SHADOW_TRANSFER_PRESCALER_SLICE_1);
  
  /* Configure start event */
  /* Configure event 0 */
  XMC_CCU8_SLICE_ConfigureEvent(SLICE1_PTR, XMC_CCU8_SLICE_EVENT_0, &START_config);
  XMC_CCU8_SLICE_StartConfig(SLICE1_PTR, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START_CLEAR);
  
  /* Get the slice out of idle mode */
  XMC_CCU8_EnableClock(MODULE_PTR, SLICE1_NUMBER);
  
  // CCU80 PWM IOs Settings
  XMC_GPIO_SetMode(P0_4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3);   // CCU80.OUT10
  
  /**********************************************************************/
  /*                   Interrupt related                                */
  /**********************************************************************/
  XMC_CCU8_SLICE_EnableEvent(SLICE0_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);  // Period Match		CCU80 SR0 	Vector No.60
  XMC_CCU8_SLICE_SetInterruptNode(SLICE0_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU8_SLICE_SR_ID_0); // Period Match connected with SR2
  XMC_CCU8_SLICE_ClearEvent(SLICE0_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);
  
  XMC_CCU8_SLICE_EnableEvent(SLICE1_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);  // Period Match		CCU80 SR1 	Vector No.61
  XMC_CCU8_SLICE_SetInterruptNode(SLICE1_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU8_SLICE_SR_ID_1); // Period Match connected with SR2
  XMC_CCU8_SLICE_ClearEvent(SLICE1_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);
  
  NVIC_SetPriority(CCU80_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),30,0));						//Vector 60 , level 30
  NVIC_EnableIRQ(CCU80_0_IRQn);
  
  NVIC_SetPriority(CCU80_1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),30,0));						//Vector 61 , level 30
  NVIC_EnableIRQ(CCU80_1_IRQn);
  
  /* Start */
  XMC_SCU_SetCcuTriggerHigh(SCU_GENERAL_CCUCON_GSC80_Msk);
  
}


void CCU80_0_IRQHandler(void)
{
  if (XMC_CCU8_SLICE_GetEvent(SLICE0_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH))
  {
    XMC_CCU8_SLICE_ClearEvent(SLICE0_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);
  }
}

void CCU80_1_IRQHandler(void)
{
  if (XMC_CCU8_SLICE_GetEvent(SLICE1_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH))
  {
    XMC_CCU8_SLICE_ClearEvent(SLICE1_PTR, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);
  }
}







