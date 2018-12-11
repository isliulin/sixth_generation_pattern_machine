#include "POSIF1.h"

/* POSIF Macros */
#define POSIF1_PTR POSIF1


/* Configuration for POSIF - Multi-Channel Mode */
const XMC_POSIF_CONFIG_t POSIF1_config =
{
  .mode   = XMC_POSIF_MODE_QD,    /**< POSIF Operational mode */
  .input0 = XMC_POSIF_INPUT_PORT_A,    /**< Choice of input for Input-1 */
  .input1 = XMC_POSIF_INPUT_PORT_A,    /**< Choice of input for Input-2 */
  .input2 = XMC_POSIF_INPUT_PORT_A,   /**< Choice of input for Input-3 */
  .filter = XMC_POSIF_FILTER_DISABLED   /**< Input filter configuration */
};

const XMC_POSIF_QD_CONFIG_t POSIF1_QD_config =
{
  .mode = XMC_POSIF_QD_MODE_QUADRATURE,
  .phase_a = XMC_POSIF_INPUT_ACTIVE_LEVEL_HIGH,
  .phase_b = XMC_POSIF_INPUT_ACTIVE_LEVEL_HIGH,
  .phase_leader = 1,
  .index = XMC_POSIF_QD_INDEX_GENERATION_ALWAYS,
};

void POSIF1_0_IRQHandler(void)
{
  
}
void POSIF1_1_IRQHandler(void)
{
  
}

void POSIF1_Init(void)
{
  // ---------------------------------------------
  // POSIF1
  // ---------------------------------------------
  XMC_GPIO_EnableDigitalInput(P2_5); // IN0A
  XMC_GPIO_EnableDigitalInput(P2_4); // IN1A
  XMC_GPIO_EnableDigitalInput(P2_3); // IN2A
  
  /* POSIF Configuration  */
  XMC_POSIF_Init(POSIF1_PTR, &POSIF1_config);
  XMC_POSIF_QD_Init(POSIF1_PTR, &POSIF1_QD_config);
  
  /* Start the POSIF module*/
  XMC_POSIF_Start(POSIF1_PTR);
}
