#ifndef BSP_CAN_H
#define BSP_CAN_H

/*----------------------------------------------------------------------------*/
//CAN 收发端口定义
#define CAN_TX_PORT      XMC_GPIO_PORT2
#define CAN_TX_PINS      XMC_GPIO_PIN07

#define CAN_RX_PORT      XMC_GPIO_PORT2
#define CAN_RX_PINS      XMC_GPIO_PIN06



/*----------------------------------------------------------------------------*/
void bsp_CanInit(void);

void bsp_CanSendBuf(uint8_t *Buf,uint8_t Len);

void bsp_CanReadBuf(uint8_t *Buf,uint8_t Len);







/*----------------------------------------------------------------------------*/
#endif /* BSP_CAN_H */

