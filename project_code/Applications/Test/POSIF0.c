#include "POSIF0.h"

/* POSIF Macros */
#define POSIF0_PTR POSIF0

/* Configuration for POSIF - Multi-Channel Mode */
const XMC_POSIF_CONFIG_t POSIF0_config =
{
  .mode   = XMC_POSIF_MODE_QD,    /**< POSIF Operational mode */
  .input0 = XMC_POSIF_INPUT_PORT_B,    /**< Choice of input for Input-1 */
  .input1 = XMC_POSIF_INPUT_PORT_B,    /**< Choice of input for Input-2 */
  .input2 = XMC_POSIF_INPUT_PORT_B,   /**< Choice of input for Input-3 */
  .filter = XMC_POSIF_FILTER_DISABLED   /**< Input filter configuration */
};

const XMC_POSIF_QD_CONFIG_t POSIF0_QD_config =
{
  .mode = XMC_POSIF_QD_MODE_QUADRATURE,
  .phase_a = XMC_POSIF_INPUT_ACTIVE_LEVEL_HIGH,
  .phase_b = XMC_POSIF_INPUT_ACTIVE_LEVEL_HIGH,
  .phase_leader = 1,
  .index = XMC_POSIF_QD_INDEX_GENERATION_ALWAYS,
};

void POSIF0_0_IRQHandler(void)
{
  
}
void POSIF0_1_IRQHandler(void)
{
  
}

void POSIF0_Init(void)
{
  // ---------------------------------------------
  // POSIF0
  // ---------------------------------------------
  XMC_GPIO_EnableDigitalInput(P14_7); // IN0B
  XMC_GPIO_EnableDigitalInput(P14_6); // IN1B
  XMC_GPIO_EnableDigitalInput(P14_5); // IN2B
  
  /* POSIF Configuration  */
  XMC_POSIF_Init(POSIF0_PTR, &POSIF0_config);
  XMC_POSIF_QD_Init(POSIF0_PTR, &POSIF0_QD_config);
  
  /* Start the POSIF module*/
  XMC_POSIF_Start(POSIF0_PTR);
  
}
