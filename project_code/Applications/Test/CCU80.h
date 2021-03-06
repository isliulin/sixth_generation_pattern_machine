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
 * @file        CCU80.h
 * @date        Nov 18, 2015
 * @version     1.0.0
 *
 * @brief       CCU80 initialization header file based on LLD
 *
 * APIs provided in this file cover the following functional blocks : <br>
 *
 * History <br>
 * Version 1.0.0    Initial <br>
 *
 ********************************************************************************************************************/
#ifndef CCU80_H_
#define CCU80_H_
/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
//#include <XMC4500.h>
#include "xmc_ccu8.h"
#include "xmc_scu.h"
/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
#define PASSIVELEVEL	0
/*********************************************************************************************************************
 * ENUMS
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * DATA STRUCTURES
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * GLOBAL ROUTINES DEFINITION
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * API IMPLEMENTATION
 ********************************************************************************************************************/
void CCU80_Init(void);

#endif /* CCU80_H_ */

