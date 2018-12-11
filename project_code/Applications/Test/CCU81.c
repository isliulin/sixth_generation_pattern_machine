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
 * @file        CCU81.c 
 * @date        Nov 18, 2015
 * @version     1.0.0
 *
 * @brief       CCU81 initialization based on LLD
 *
 * APIs provided in this file cover the following functional blocks : <br>
 *
 * History <br>
 * Version 0.1.0    Initial <br>
 *
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include "CCU81.h"

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * ENUMS
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * DATA STRUCTURES
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * LOCAL DATA
 ********************************************************************************************************************/
static const XMC_CCU8_SLICE_COMPARE_CONFIG_t CCU81_slide_config =
{
  .timer_mode 		   = (uint32_t) XMC_CCU8_SLICE_TIMER_COUNT_MODE_CA,
  .monoshot   		   = (uint32_t) false,
  .shadow_xfer_clear   = (uint32_t) 0U,
  .dither_timer_period = (uint32_t) 0U,
  .dither_duty_cycle   = (uint32_t) 0U,

  .mcm_ch1_enable 	   = (uint32_t) false,
  .mcm_ch2_enable 	   = (uint32_t) false,

  .slice_status 	   = (uint32_t) XMC_CCU8_SLICE_STATUS_CHANNEL_1,

  .prescaler_mode	   = (uint32_t) XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL,

#if PASSIVELEVEL
  .passive_level_out0  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
  .passive_level_out1  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
  .passive_level_out2  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
  .passive_level_out3  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
#else
  .passive_level_out0  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out1  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out2  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out3  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
#endif
  .asymmetric_pwm	   = (uint32_t) 1U,

  .invert_out0	   	   = (uint32_t) 0U,
  .invert_out1	   	   = (uint32_t) 1U,
  .invert_out2	   	   = (uint32_t) 0U,
  .invert_out3	   	   = (uint32_t) 1U,

  .prescaler_initval   = (uint32_t) 0U,
  .float_limit		   = (uint32_t) 0U,
  .dither_limit		   = (uint32_t) 0U,
  .timer_concatenation = (uint32_t) 0U
};

static const XMC_CCU8_SLICE_COMPARE_CONFIG_t CCU81_slide_config_test =
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

#if PASSIVELEVEL
  .passive_level_out0  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
  .passive_level_out1  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
  .passive_level_out2  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
  .passive_level_out3  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
#else
  .passive_level_out0  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out1  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out2  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
  .passive_level_out3  = (uint32_t) XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
#endif
  .asymmetric_pwm	   = (uint32_t) 0U,

  .invert_out0	   	   = (uint32_t) 0U,
  .invert_out1	   	   = (uint32_t) 1U,
  .invert_out2	   	   = (uint32_t) 0U,
  .invert_out3	   	   = (uint32_t) 1U,

  .prescaler_initval   = (uint32_t) 3U,
  .float_limit		   = (uint32_t) 0U,
  .dither_limit		   = (uint32_t) 0U,
  .timer_concatenation = (uint32_t) 0U
};

static const XMC_CCU8_SLICE_EVENT_CONFIG_t START_MODULATION_config =
{
  .mapped_input = XMC_CCU8_SLICE_INPUT_H, // SCU.GLCCST81
  .edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE, // Rising edge for start
  .level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_LOW, // Low level active for modulation
  .duration = XMC_CCU8_SLICE_EVENT_FILTER_7_CYCLES
};

static const XMC_CCU8_SLICE_EVENT_CONFIG_t TRAP_config =
{
  .mapped_input = XMC_CCU8_SLICE_INPUT_A, // P5.0
  .edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
  .level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_LOW,
  .duration = XMC_CCU8_SLICE_EVENT_FILTER_7_CYCLES
};
/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * LOCAL ROUTINES DEFINITION
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * GLOBAL ROUTINES DEFINITION
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/
/*********************************************************************************************************
** 函数名称: void CCU81_Init(void)
** 功能描述: 初始化CCU81相关寄存器
**
** 说　 明: 	CCU81-(CC80-CC81-CC82), 输出3对互补带死区PWM,无效电平由PASSIVELEVEL定义。
**
** 			CCU81_CC80-CCU81.out00		P1_15	U-
**			CCU81_CC80-CCU81.out01		P1_12	U+
**			CCU81_CC81-CCU81.out10		P1_14	V-
**			CCU81_CC81-CCU81.out11		P1_11	V+
**			CCU81_CC82-CCU81.out20		P1_13	W-
**			CCU81_CC82-CCU81.out21		P1_10	W+
**			TRAP						P5_0	C-Trap-2
**
**			Passive level 	->	Low
**			the higher the Compare register is, the MCU output duty cycle is lower,  the real signal to IGBT is lower
**			As a result , when period match, all the three low side IGBT is ON
**
**
**			PWM CC80 1中断，触发CCU81SR2，触发4路ADC,具体AD内容见ADC.C
**			P0_6下降沿对应period match 时， 双电阻触发AD
**
**
**
**********************************************************************************************************/
void CCU81_Init(uint32_t Period_Value, uint32_t DeadTime_Value)
{
	XMC_CCU8_SLICE_DEAD_TIME_CONFIG_t Dead_Time_Config;

	/* Configure dead time */
	Dead_Time_Config.enable_dead_time_channel1 = 1;
	Dead_Time_Config.enable_dead_time_channel2 = 1;
	Dead_Time_Config.channel1_st_path = 1;
	Dead_Time_Config.channel1_inv_st_path = 1;
	Dead_Time_Config.channel2_st_path = 1;
	Dead_Time_Config.channel2_inv_st_path = 1;
	Dead_Time_Config.channel1_st_rising_edge_counter = DeadTime_Value;
	Dead_Time_Config.channel1_st_falling_edge_counter = DeadTime_Value;
	Dead_Time_Config.channel2_st_rising_edge_counter = DeadTime_Value;
	Dead_Time_Config.channel2_st_falling_edge_counter = DeadTime_Value;
	Dead_Time_Config.div = 0;

	/* Enable clock, enable prescaler block and configure global control */
	XMC_CCU8_Init(CCU81, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

	/* Start the prescaler and restore clocks to slices */
	XMC_CCU8_StartPrescaler(CCU81);

	/* Start of CCU8 configurations */
	/* Ensure fCCU reaches CCU80 */
	XMC_CCU8_SetModuleClock(CCU81, XMC_CCU8_CLOCK_SCU);

	/**********************************************************************/
	/*                   CC80 configuration                               */
	/**********************************************************************/
	/* Configure CCU8x_CC8y slice as timer */
	XMC_CCU8_SLICE_CompareInit(CCU81_CC80, &CCU81_slide_config);

	/* Set period match value of the timer  */
	XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU81_CC80, Period_Value);
	/* Set timer compare match value for channel 1 - 50% duty */
	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC80, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, (Period_Value >> 1));
	/* Set timer compare match value for channel 2 - 50% duty */
	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC80, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, (Period_Value >> 1));

	/* Configure dead time */
	XMC_CCU8_SLICE_DeadTimeInit(CCU81_CC80, &Dead_Time_Config);

	/* Transfer value from shadow timer registers to actual timer registers */
	XMC_CCU8_EnableShadowTransfer(CCU81, XMC_CCU8_SHADOW_TRANSFER_SLICE_0);

	/* Configure trap event */
	/* Trap exit is synchronized to PWM signal*/
	XMC_CCU8_SLICE_TrapConfig(CCU81_CC80, XMC_CCU8_SLICE_TRAP_EXIT_MODE_SW, 1U);
	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC80, XMC_CCU8_SLICE_EVENT_2, &TRAP_config);

	/* Enable events: Trap*/
	XMC_CCU8_SLICE_EnableTrap(CCU81_CC80, \
		(uint32_t) (XMC_CCU8_SLICE_OUTPUT_0 | XMC_CCU8_SLICE_OUTPUT_1 | \
		XMC_CCU8_SLICE_OUTPUT_2 | XMC_CCU8_SLICE_OUTPUT_3));

	/* Configure start and modulation event */
	/* Configure event 0 */
	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC80, XMC_CCU8_SLICE_EVENT_0, &START_MODULATION_config);

	/* Configure start and modulation */
	XMC_CCU8_SLICE_StartConfig(CCU81_CC80, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START);
	XMC_CCU8_SLICE_ModulationConfig(CCU81_CC80,  XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_MODULATION_MODE_CLEAR_OUT, \
			XMC_CCU8_SLICE_MODULATION_CHANNEL_1_AND_2, 1U);

	/* Get the slice out of idle mode */
	XMC_CCU8_EnableClock(CCU81, 0);

	/**********************************************************************/
	/*                   CC81 configuration                               */
	/**********************************************************************/
	/* Configure CCU8x_CC8y slice as timer */
	XMC_CCU8_SLICE_CompareInit(CCU81_CC81, &CCU81_slide_config);

	/* Set period match value of the timer  */
	XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU81_CC81, Period_Value);
	/* Set timer compare match value for channel 1 - 50% duty */
	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC81, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, (Period_Value >> 1));
	/* Set timer compare match value for channel 2 - 50% duty */
	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC81, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, (Period_Value >> 1));

	/* Configure dead time */
	XMC_CCU8_SLICE_DeadTimeInit(CCU81_CC81, &Dead_Time_Config);

	/* Transfer value from shadow timer registers to actual timer registers */
	XMC_CCU8_EnableShadowTransfer(CCU81, XMC_CCU8_SHADOW_TRANSFER_SLICE_1);

	/* Configure trap event */
	/* Trap exit is synchronized to PWM signal*/
	XMC_CCU8_SLICE_TrapConfig(CCU81_CC81, XMC_CCU8_SLICE_TRAP_EXIT_MODE_SW, 1U);
	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC81, XMC_CCU8_SLICE_EVENT_2, &TRAP_config);

	/* Enable events: Trap*/
	XMC_CCU8_SLICE_EnableTrap(CCU81_CC81, \
		(uint32_t) (XMC_CCU8_SLICE_OUTPUT_0 | XMC_CCU8_SLICE_OUTPUT_1 | \
		XMC_CCU8_SLICE_OUTPUT_2 | XMC_CCU8_SLICE_OUTPUT_3));

	/* Configure start and modulation event */
	/* Configure event 0 */
	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC81, XMC_CCU8_SLICE_EVENT_0, &START_MODULATION_config);

	/* Configure start and modulation */
	XMC_CCU8_SLICE_StartConfig(CCU81_CC81, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START);
	XMC_CCU8_SLICE_ModulationConfig(CCU81_CC81,  XMC_CCU8_SLICE_EVENT_0,  XMC_CCU8_SLICE_MODULATION_MODE_CLEAR_OUT, \
			XMC_CCU8_SLICE_MODULATION_CHANNEL_1_AND_2, 1U);

	/* Get the slice out of idle mode */
	XMC_CCU8_EnableClock(CCU81, 1);

	/**********************************************************************/
	/*                   CC82 configuration                               */
	/**********************************************************************/
	/* Configure CCU8x_CC8y slice as timer */
	XMC_CCU8_SLICE_CompareInit(CCU81_CC82, &CCU81_slide_config);

	/* Set period match value of the timer  */
	XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU81_CC82, Period_Value);
	/* Set timer compare match value for channel 1 - 50% duty */
	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC82, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, (Period_Value >> 1));
	/* Set timer compare match value for channel 2 - 50% duty */
	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC82, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, (Period_Value >> 1));

	/* Configure dead time */
	XMC_CCU8_SLICE_DeadTimeInit(CCU81_CC82, &Dead_Time_Config);

	/* Transfer value from shadow timer registers to actual timer registers */
	XMC_CCU8_EnableShadowTransfer(CCU81, XMC_CCU8_SHADOW_TRANSFER_SLICE_2);

	/* Configure trap event */
	/* Trap exit is synchronized to PWM signal*/
	XMC_CCU8_SLICE_TrapConfig(CCU81_CC82, XMC_CCU8_SLICE_TRAP_EXIT_MODE_SW, 1U);
	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC82, XMC_CCU8_SLICE_EVENT_2, &TRAP_config);

	/* Enable events: Trap*/
	XMC_CCU8_SLICE_EnableTrap(CCU81_CC82, \
		(uint32_t) (XMC_CCU8_SLICE_OUTPUT_0 | XMC_CCU8_SLICE_OUTPUT_1 | \
		XMC_CCU8_SLICE_OUTPUT_2 | XMC_CCU8_SLICE_OUTPUT_3));

	/* Configure start and modulation event */
	/* Configure event 0 */
	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC82, XMC_CCU8_SLICE_EVENT_0, &START_MODULATION_config);

	/* Configure start and modulation */
	XMC_CCU8_SLICE_StartConfig(CCU81_CC82, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START);
	XMC_CCU8_SLICE_ModulationConfig(CCU81_CC82,  XMC_CCU8_SLICE_EVENT_0,  XMC_CCU8_SLICE_MODULATION_MODE_CLEAR_OUT, \
			XMC_CCU8_SLICE_MODULATION_CHANNEL_1_AND_2, 1U);

	/* Get the slice out of idle mode */
	XMC_CCU8_EnableClock(CCU81, 2);

	/**********************************************************************/
	/*                   CC83 configuration (for test)                    */
	/**********************************************************************/
	/* Configure CCU8x_CC8y slice as timer */
	XMC_CCU8_SLICE_CompareInit(CCU81_CC83, &CCU81_slide_config_test);

	/* Set period match value of the timer  */
	XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU81_CC83, 10000);
	/* Set timer compare match value for channel 1 - 50% duty */
//	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC83, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, 3500);
	/* Set timer compare match value for channel 2 - 50% duty */
	XMC_CCU8_SLICE_SetTimerCompareMatch(CCU81_CC83, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, 5000);

  XMC_CCU8_SLICE_SetTimerValue(CCU81_CC83, (5000-1));

	/* Configure dead time */
//	XMC_CCU8_SLICE_DeadTimeInit(CCU81_CC82, &Dead_Time_Config);

	/* Transfer value from shadow timer registers to actual timer registers */
	XMC_CCU8_EnableShadowTransfer(CCU81, XMC_CCU8_SHADOW_TRANSFER_SLICE_3);

	/* Configure trap event */
	/* Trap exit is synchronized to PWM signal*/
//	XMC_CCU8_SLICE_TrapConfig(CCU81_CC82, XMC_CCU8_SLICE_TRAP_EXIT_MODE_SW, 1U);
//	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC82, XMC_CCU8_SLICE_EVENT_2, &TRAP_config);

	/* Enable events: Trap*/
//	XMC_CCU8_SLICE_EnableTrap(CCU81_CC82, \
//		(uint32_t) (XMC_CCU8_SLICE_OUTPUT_0 | XMC_CCU8_SLICE_OUTPUT_1 | \
//		XMC_CCU8_SLICE_OUTPUT_2 | XMC_CCU8_SLICE_OUTPUT_3));

	/* Configure start and modulation event */
	/* Configure event 0 */
//	XMC_CCU8_SLICE_ConfigureEvent(CCU81_CC83, XMC_CCU8_SLICE_EVENT_0, &START_MODULATION_config);

//	/* Configure start and modulation */
//	XMC_CCU8_SLICE_StartConfig(CCU81_CC83, XMC_CCU8_SLICE_EVENT_0, XMC_CCU8_SLICE_START_MODE_TIMER_START);
//	XMC_CCU8_SLICE_ModulationConfig(CCU81_CC83,  XMC_CCU8_SLICE_EVENT_0,  XMC_CCU8_SLICE_MODULATION_MODE_CLEAR_OUT, \
//			XMC_CCU8_SLICE_MODULATION_CHANNEL_1_AND_2, 1U);

	/* Get the slice out of idle mode */
	XMC_CCU8_EnableClock(CCU81, 3);
	
	XMC_CCU8_SLICE_StartTimer(CCU81_CC83);

	/**********************************************************************/
	/*                   Interrupt related                                */
	/**********************************************************************/
	XMC_CCU8_SLICE_EnableEvent(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_EVENT2);     // Enable One Match and Event2 (trap)
	XMC_CCU8_SLICE_EnableEvent(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);  // Period Match		CCU80 SR2 	Vector No.62

	XMC_CCU8_SLICE_SetInterruptNode(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_EVENT2, XMC_CCU8_SLICE_SR_ID_1); // Event2 connected with SR1
	XMC_CCU8_SLICE_SetInterruptNode(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU8_SLICE_SR_ID_2); // Period Match connected with SR2

	XMC_CCU8_SLICE_ClearEvent(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_EVENT2);
	XMC_CCU8_SLICE_ClearEvent(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_TRAP);
	XMC_CCU8_SLICE_ClearEvent(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);

	XMC_CCU8_SLICE_ClearEvent(CCU81_CC81, XMC_CCU8_SLICE_IRQ_ID_EVENT2);
	XMC_CCU8_SLICE_ClearEvent(CCU81_CC81, XMC_CCU8_SLICE_IRQ_ID_TRAP);
	XMC_CCU8_SLICE_ClearEvent(CCU81_CC81, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);

	XMC_CCU8_SLICE_ClearEvent(CCU81_CC82, XMC_CCU8_SLICE_IRQ_ID_EVENT2);
	XMC_CCU8_SLICE_ClearEvent(CCU81_CC82, XMC_CCU8_SLICE_IRQ_ID_TRAP);
	XMC_CCU8_SLICE_ClearEvent(CCU81_CC82, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);

	NVIC_SetPriority(CCU81_2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),29,0));						//Vector 62 , level 30
	NVIC_EnableIRQ(CCU81_2_IRQn);

	NVIC_SetPriority(CCU81_1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),19,0));						//vector 61, level 20 (higher priority)
	NVIC_EnableIRQ(CCU81_1_IRQn);
}










