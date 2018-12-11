//XMC Lib Project includes:
#include "CCU40.h"


//Project Macro definitions:
#define MODULE_PTR      	CCU40
#define MODULE_NUMBER   	(0U)

#define SLICE0_PTR       	CCU40_CC40
#define SLICE0_NUMBER    	(0U)

#define SLICE1_PTR       	CCU40_CC41
#define SLICE1_NUMBER    	(1U)

//XMC Capture/Compare Unit 4 (CCU4) Configuration:
XMC_CCU4_SLICE_COMPARE_CONFIG_t SLICE0_config =
{
  .timer_mode = (uint32_t) XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot = (uint32_t) false,
  .shadow_xfer_clear = (uint32_t) 0,
  .dither_timer_period = (uint32_t) 0,
  .dither_duty_cycle = (uint32_t) 0,
  .prescaler_mode = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .mcm_enable = (uint32_t) 0,
  .prescaler_initval = (uint32_t) 4, 	/* 80MHz/16 = 5MHz */
  .float_limit = (uint32_t) 0,
  .dither_limit = (uint32_t) 0,
  .passive_level = (uint32_t) XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .timer_concatenation = (uint32_t) 0
};

XMC_CCU4_SLICE_COMPARE_CONFIG_t SLICE1_config =
{
  .timer_mode = (uint32_t) XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
  .monoshot = (uint32_t) false,
  .shadow_xfer_clear = (uint32_t) 0,
  .dither_timer_period = (uint32_t) 0,
  .dither_duty_cycle = (uint32_t) 0,
  .prescaler_mode = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
  .mcm_enable = (uint32_t) 0,
  .prescaler_initval = (uint32_t) 4, 	/* 80MHz/16 = 5MHz */
  .float_limit = (uint32_t) 0,
  .dither_limit = (uint32_t) 0,
  .passive_level = (uint32_t) XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .timer_concatenation = (uint32_t) 0
};

XMC_CCU4_SLICE_EVENT_CONFIG_t SLICE0_EVENT0 = {
  .mapped_input = XMC_CCU4_SLICE_INPUT_E, // CCU40.IN0E
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
  
};

XMC_CCU4_SLICE_EVENT_CONFIG_t SLICE0_EVENT1 = {
  .mapped_input = XMC_CCU4_SLICE_INPUT_F, // CCU40.IN0F
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
  .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_COUNT_UP_ON_HIGH,
  
};

XMC_CCU4_SLICE_EVENT_CONFIG_t SLICE1_EVENT0 = {
  .mapped_input = XMC_CCU4_SLICE_INPUT_H, // CCU40.IN1H
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
  
};

/* The CCU40 interrupt handler function was created to periodically modify the timer
* compare match values to achieve a PWM duty cycle between 33.3% and 66.7%.
*/
//void CCU40_0_IRQHandler(void)
//{
//  /* Clear pending interrupt */
//  XMC_CCU4_SLICE_ClearEvent(SLICE0_PTR,XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
//  
//  
//}

void CCU40_Init(void)
{
  
  /* Enable clock, enable prescaler block and configure global control */
  XMC_CCU4_Init(MODULE_PTR, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
  
  /* Start the prescaler and restore clocks to slices */
  XMC_CCU4_StartPrescaler(MODULE_PTR);
  
  /* Start of CCU4 configurations */
  /* Ensure fCCU reaches CCU40 */
  XMC_CCU4_SetModuleClock(MODULE_PTR, XMC_CCU4_CLOCK_SCU);
  
  /*****************************************************************/
  /*                     Slice 0                                   */
  /*****************************************************************/
  //�	Configure Slice(s) Functions, Interrupts and Start-up
  /* Initialize the Slice */
  XMC_CCU4_SLICE_CompareInit(SLICE0_PTR, &SLICE0_config);
  
  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE0_PTR, 1000);
  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE0_PTR, 2000); // 50000 * (1/5MHz) = 10ms
  
  /* Configure count event */
  XMC_CCU4_SLICE_ConfigureEvent(SLICE0_PTR, XMC_CCU4_SLICE_EVENT_0, &SLICE0_EVENT0);
  XMC_CCU4_SLICE_CountConfig(SLICE0_PTR, XMC_CCU4_SLICE_EVENT_0);
  
  /* Configure direction event */
  XMC_CCU4_SLICE_ConfigureEvent(SLICE0_PTR, XMC_CCU4_SLICE_EVENT_1, &SLICE0_EVENT1);
  XMC_CCU4_SLICE_DirectionConfig(SLICE0_PTR, XMC_CCU4_SLICE_EVENT_1);
  
  /* Enable compare match events */
  XMC_CCU4_SLICE_EnableEvent(SLICE0_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
  
  /* Connect compare match event to SR0 */
  XMC_CCU4_SLICE_SetInterruptNode(SLICE0_PTR, \
    XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);
  
  /*****************************************************************/
  /*                     Slice 1                                   */
  /*****************************************************************/
  //    Configure Slice(s) Functions, Interrupts and Start-up
  /* Initialize the Slice */
  XMC_CCU4_SLICE_CompareInit(SLICE1_PTR, &SLICE1_config);
  
  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE1_PTR, 1000);
  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE1_PTR, 2000); // 50000 * (1/5MHz) = 10ms
  
  /* Configure count event */
  XMC_CCU4_SLICE_ConfigureEvent(SLICE1_PTR, XMC_CCU4_SLICE_EVENT_0, &SLICE1_EVENT0);
  XMC_CCU4_SLICE_CountConfig(SLICE1_PTR, XMC_CCU4_SLICE_EVENT_0);
  
  /* Enable compare match events */
  XMC_CCU4_SLICE_EnableEvent(SLICE1_PTR, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
  
  /* Connect compare match event to SR0 */
  //	XMC_CCU4_SLICE_SetInterruptNode(SLICE1_PTR, \
  //			XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);
  
  /*****************************************************************/
  /*                     Shadow transfer                           */
  /*****************************************************************/
  /* Enable shadow transfer */
  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, 	\
    (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0 | XMC_CCU4_SHADOW_TRANSFER_SLICE_1 |	\
      XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0 | XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_1));
  
  /*****************************************************************/
  /*                    Interrupt                                  */
  /*****************************************************************/
  /* Set NVIC priority */
  NVIC_SetPriority(CCU40_0_IRQn, 3U);
  
  /* Enable IRQ */
  NVIC_EnableIRQ(CCU40_0_IRQn);
  
  /*****************************************************************/
  /*                    Enable clock                               */
  /*****************************************************************/
  /* Get the slice out of idle mode */
  XMC_CCU4_EnableClock(MODULE_PTR, SLICE0_NUMBER);
  XMC_CCU4_EnableClock(MODULE_PTR, SLICE1_NUMBER);
  
  /*****************************************************************/
  /*                    Start                                      */
  /*****************************************************************/
  //Start Timer Running
  XMC_CCU4_SLICE_StartTimer(SLICE0_PTR);
  XMC_CCU4_SLICE_StartTimer(SLICE1_PTR);
  
}

