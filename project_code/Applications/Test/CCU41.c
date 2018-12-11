/* This example uses a slice of CCU4 (CCU40 Slice 0) to generate a PWM signal (output to P0.0).
* The CCU4 slice is configured in edged aligned mode with a frequency of 1Hz. An interrupt is
* generated on every compare match event, which alternates the PWM duty cycle between 33.3%
* and 66.7%. The CCU4 slice is started by an external start event on Event 0 connected to SCU.GSC40.
* It is targeted for XMC1200.
*/

/* Version History
* Version	Date				Changes
* v1.0		20 July 2015		Initial Verison
* v1.1		8 September 2015	Ported to DAVE v4.1.2
*/

//XMC Lib Project includes:
#include "CCU41.h"


//XMC Capture/Compare Unit 4 (CCU4) Configuration:
static const XMC_CCU4_SLICE_COMPARE_CONFIG_t SLICE0_config =
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

static const XMC_CCU4_SLICE_COMPARE_CONFIG_t SLICE1_config =
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

static const XMC_CCU4_SLICE_EVENT_CONFIG_t SLICE0_EVENT0 = {
  .mapped_input = XMC_CCU4_SLICE_INPUT_E, // CCU40.IN0E
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
  
};

static const XMC_CCU4_SLICE_EVENT_CONFIG_t SLICE0_EVENT1 = {
  .mapped_input = XMC_CCU4_SLICE_INPUT_F, // CCU40.IN0F
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
  .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_COUNT_UP_ON_HIGH,
  
};

static const XMC_CCU4_SLICE_EVENT_CONFIG_t SLICE1_EVENT0 = {
  .mapped_input = XMC_CCU4_SLICE_INPUT_H, // CCU40.IN1H
  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
  
};

/* The CCU40 interrupt handler function was created to periodically modify the timer
* compare match values to achieve a PWM duty cycle between 33.3% and 66.7%.
*/
void CCU41_0_IRQHandler(void)
{
  /* Clear pending interrupt */
  XMC_CCU4_SLICE_ClearEvent(CCU41_CC40, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
}

void CCU41_Init(void)
{
  
  /* Enable clock, enable prescaler block and configure global control */
  XMC_CCU4_Init(CCU41, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
  
  /* Start the prescaler and restore clocks to slices */
  XMC_CCU4_StartPrescaler(CCU41);
  
  /* Start of CCU4 configurations */
  /* Ensure fCCU reaches CCU40 */
  XMC_CCU4_SetModuleClock(CCU41, XMC_CCU4_CLOCK_SCU);
  
  /*****************************************************************/
  /*                     Slice 0                                   */
  /*****************************************************************/
  //�	Configure Slice(s) Functions, Interrupts and Start-up
  /* Initialize the Slice */
  XMC_CCU4_SLICE_CompareInit(CCU41_CC40, &SLICE0_config);
  
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU41_CC40, 10000);
  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU41_CC40, 20000U); // 50000 * (1/5MHz) = 10ms
  
  /* Configure count event */
  XMC_CCU4_SLICE_ConfigureEvent(CCU41_CC40, XMC_CCU4_SLICE_EVENT_0, &SLICE0_EVENT0);
  XMC_CCU4_SLICE_CountConfig(CCU41_CC40, XMC_CCU4_SLICE_EVENT_0);
  
  /* Configure direction event */
  XMC_CCU4_SLICE_ConfigureEvent(CCU41_CC40, XMC_CCU4_SLICE_EVENT_1, &SLICE0_EVENT1);
  XMC_CCU4_SLICE_DirectionConfig(CCU41_CC40, XMC_CCU4_SLICE_EVENT_1);
  
  /* Enable compare match events */
  XMC_CCU4_SLICE_EnableEvent(CCU41_CC40, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
  
  /* Connect compare match event to SR0 */
  XMC_CCU4_SLICE_SetInterruptNode(CCU41_CC40, \
    XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);
  
  /*****************************************************************/
  /*                     Slice 1                                   */
  /*****************************************************************/
  //�	Configure Slice(s) Functions, Interrupts and Start-up
  /* Initialize the Slice */
  XMC_CCU4_SLICE_CompareInit(CCU41_CC41, &SLICE1_config);
  
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU41_CC41, 10000);
  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU41_CC41, 20000U); // 50000 * (1/5MHz) = 10ms
  
  /* Configure count event */
  XMC_CCU4_SLICE_ConfigureEvent(CCU41_CC41, XMC_CCU4_SLICE_EVENT_0, &SLICE1_EVENT0);
  XMC_CCU4_SLICE_CountConfig(CCU41_CC41, XMC_CCU4_SLICE_EVENT_0);
  
  /* Enable compare match events */
  XMC_CCU4_SLICE_EnableEvent(CCU41_CC41, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
  
  /* Connect compare match event to SR0 */
  //	XMC_CCU4_SLICE_SetInterruptNode(SLICE1_PTR, \
  //			XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);
  
  /*****************************************************************/
  /*                     Shadow transfer                           */
  /*****************************************************************/
  /* Enable shadow transfer */
  XMC_CCU4_EnableShadowTransfer(CCU41, 	\
    (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0 | XMC_CCU4_SHADOW_TRANSFER_SLICE_1 |	\
      XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0 | XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_1));
  
  /*****************************************************************/
  /*                    Interrupt                                  */
  /*****************************************************************/
  /* Set NVIC priority */
  NVIC_SetPriority(CCU41_0_IRQn, 3U);
  
  /* Enable IRQ */
  NVIC_EnableIRQ(CCU41_0_IRQn);
  
  /*****************************************************************/
  /*                    Enable clock                               */
  /*****************************************************************/
  /* Get the slice out of idle mode */
  XMC_CCU4_EnableClock(CCU41, 0);
  XMC_CCU4_EnableClock(CCU41, 1);
  
  /*****************************************************************/
  /*                    Start                                      */
  /*****************************************************************/
  //Start Timer Running
  XMC_CCU4_SLICE_StartTimer(CCU41_CC40);
  XMC_CCU4_SLICE_StartTimer(CCU41_CC41);
  
}

