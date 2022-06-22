/*
 * ADC_MSP432_CONFIG.h
 *
 *  Created on: Jun 16, 2022
 *      Author: Administrador
 */

//#define __MSP432P401R__
//#include <ti/devices/msp432p4xx/inc/msp.h>
#include "msp.h"
#ifndef DRIVERS_ADC_MSP432_CONFIG_H_
#define DRIVERS_ADC_MSP432_CONFIG_H_

/*7 pasos para la creacion de un Driver*/
/*
 * 1 - Definir la tabla de configuracion
 * 2 - Definir los canales perifericos
 * 3 - Completar la tabla de configuracion
 * 4 - Crear las matrices de punteros.
 * 5 - Crear funcion de inicializacion
 * 6 - Completar interfaz de configurador
 */


/*Tabla de configuracion*/
#define PERBASE                              ((uint32_t)0x40000000)          /*!< Peripherals start address */
#define ADC14BASE                            (PERBASE +0x00012000)          /*!< Base address of module ADC14 registers */
#define ADC_14                            ((ADC14_Tipo *) ADC14BASE)
//#endif /* DRIVERS_ADC_MSP432_CONFIG_H_ */

/******************************************************************************
* ADC14 Registers
******************************************************************************/
/** @addtogroup ADC14 MSP432P401R (ADC14)
  @{
*/
typedef struct {
  __IO uint32_t CTL0;                                                            /*!< Control 0 Register */
  __IO uint32_t CTL1;                                                            /*!< Control 1 Register */
  __IO uint32_t LO0;                                                             /*!< Window Comparator Low Threshold 0 Register */
  __IO uint32_t HI0;                                                             /*!< Window Comparator High Threshold 0 Register */
  __IO uint32_t LO1;                                                             /*!< Window Comparator Low Threshold 1 Register */
  __IO uint32_t HI1;                                                             /*!< Window Comparator High Threshold 1 Register */
  __IO uint32_t MCTL[32];                                                        /*!< Conversion Memory Control Register */
  __IO uint32_t MEM[32];                                                         /*!< Conversion Memory Register */
       uint32_t RESERVED0[9];
  __IO uint32_t IER0;                                                            /*!< Interrupt Enable 0 Register */
  __IO uint32_t IER1;                                                            /*!< Interrupt Enable 1 Register */
  __I  uint32_t IFGR0;                                                           /*!< Interrupt Flag 0 Register */
  __I  uint32_t IFGR1;                                                           /*!< Interrupt Flag 1 Register */
  __O  uint32_t CLRIFGR0;                                                        /*!< Clear Interrupt Flag 0 Register */
  __IO uint32_t CLRIFGR1;                                                        /*!< Clear Interrupt Flag 1 Register */
  __IO uint32_t IV;                                                              /*!< Interrupt Vector Register */
} ADC14_Tipo;

#endif
