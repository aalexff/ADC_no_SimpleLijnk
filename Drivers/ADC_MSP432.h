/*
 * ADC.h
 *
 *  Created on: Jun 5, 2022
 *      Author: Alex Armando Figueroa Hernandez - 17061169
 *      Documentacion de ADC en Maual de Simplelink
 */

#include "ADC_MSP432_CONFIG.h"
#ifndef DRIVERS_ADC_H_
#define DRIVERS_ADC_H_
#define ptr *

/*
 * Definicion de voltajes de referencia.
 * Se encuentra en msp432p401r.h
 * tabla 4.2
 */

#define adcVccVss           ((uint32_t)0x00000100) /*!< V(R+) = AVCC, V(R-) = AVSS */
#define adcVrefVss          ((uint32_t)0x00000200) /*!< V(R+) = VREF buffered, V(R-) = AVSS */
#define adcVrefCVss         ((uint32_t)0x00000E00) /*!< V(R+) = VeREF+, V(R-) = VeREF- */
#define adcVerefBufVeref    ((uint32_t)0x00000F00) /*!< V(R+) = VeREF+ buffered, V(R-) = VeREF */

/*
 * Definicion de resoluciones de ADC
 */

#define adc8BitRes      ((uint32_t)0x00000000) /*!< 8 bit (9 clock cycle conversion time) */
#define adc10BitRes     ((uint32_t)0x00000010) /*!< 10 bit (11 clock cycle conversion time) */
#define adc12BitRes     ((uint32_t)0x00000020) /*!< 12 bit (14 clock cycle conversion time) */
#define adc14BitRes     ((uint32_t)0x00000030) /*!< 14 bit (16 clock cycle conversion time) */

/*
 * Definicion de divisores de reloj de ADC, son 8 divisores
 */

#define adcClkDiv1 ((uint32_t)0x00000000)   /*!< /1 */
#define adcClkDiv2 ((uint32_t)0x00400000)   /*!< /2 */
#define adcClkDiv3 ((uint32_t)0x00800000)   /*!< /3 */
#define adcClkDiv4 ((uint32_t)0x00C00000)   /*!< /4 */
#define adcClkDiv5 ((uint32_t)0x01000000)   /*!< /5 */
#define adcClkDiv6 ((uint32_t)0x01400000)   /*!< /6 */
#define adcClkDiv7 ((uint32_t)0x01800000)   /*!< /7 */
#define adcClkDiv8 ((uint32_t)0x01C00000)   /*!< /8 */

/*
 * Definicion de predivisores de reloj de ADC
 */

#define adcClkPreDiv1 ((uint32_t)0x00000000)          /*!< Predivide by 1 */
#define adcClkPreDiv4 ((uint32_t)0x40000000)          /*!< Predivide by 4 */
#define adcClkPreDiv32 ((uint32_t)0x80000000)          /*!< Predivide by 32 */
#define adcClkPreDiv64 ((uint32_t)0xC0000000)          /*!< Predivide by 64 */

/*
 * Definicion de modos de coneccion
 */

#define adcSingleChannel                ((uint32_t)0x00000000)  /*!< Single-channel, single-conversion */
#define adcSequenceChannels             ((uint32_t)0x00020000) /*!< Sequence-of-channels */
#define adcRepeatSingleChannel          ((uint32_t)0x00040000) /*!< Repeat-single-channel */
#define adcRepeatSequenceChannels       ((uint32_t)0x00060000)  /*!< Repeat-sequence-of-channels */

// Selecciona la fuente de reloj del módulo

#define adcModSource ((uint32_t)0x00000000)          /*!< MODCLK */
#define adcSysSource ((uint32_t)0x00080000)          /*!< SYSCLK */
#define adcASource ((uint32_t)0x00100000)              /*!< ACLK */
#define adcMSource ((uint32_t)0x00180000)            /*!< MCLK */
#define adcSMSource ((uint32_t)0x00200000)         /*!< SMCLK */
#define adcHSSource ((uint32_t)0x00280000)


//Estos bits definen el número de ciclos ADC14CLK
//en el período de muestreo para los registros ADC14MEM0 a ADC14MEM7

#define adcFs4      ((uint32_t)0x00000000)     /*!< 4 */
#define adcFs8      ((uint32_t)0x00001000)     /*!< 8 */
#define adcFs16     ((uint32_t)0x00002000)     /*!< 16 */
#define adcFs32     ((uint32_t)0x00003000)     /*!< 32 */
#define adcFs64     ((uint32_t)0x00004000)     /*!< 64 */
#define adcFs96     ((uint32_t)0x00005000)     /*!< 96 */
#define adcFs128    ((uint32_t)0x00006000)     /*!< 128 */
#define adcFs192    ((uint32_t)0x00007000)     /*!< 192 */

/*
 * Definiciones de control de canales
 */

#define MAX_ADC_VALUE   16383  // (2 ^14 bits)
#define ioAdcRunChannel     (0x10000000) //Mientras esta bandera está activa, el canal está corriendo.
#define ioAdcFireTrigger    (0x10000001) //Mientras esta bandera está activa, se dispara el trigger.
#define ioAdcStopChannel    (0x10000002) //Si esta bandera está activa, se detiene el canal.
#define ioAdcStopChannels   (0x10000003) //Si esta bandera esta activa, se detienen todos los canales.
#define ioAdcPauseChannel   (0x10000004) //Si esta bandera esta activa, se pausan el canal.
#define ioAdcPauseChannels  (0x10000005) //Si esta bandera esta activa, se pausan todos los canales.
#define ioAdcResumeChannel  (0x10000006) //Mientras esta bandera está activa, el canal está activo y ha sido re-iniciado.
#define ioAdcResumeChannels (0x10000007) //Mientras esta bandera esta activa, todos los canales se activan y re-inician.

/*
 * Definiciones de medicion de canales ADC
 */

#define adcMeasureLoop (0x00) //Se realiza una medicion bajo el esquema de tiempo del modulo timer32_1
#define adcStartNow (0x01) //Se inicia el timer, y la medicion comienza desde el inicio
#define adcStartTrigger (0x02) //Se realiza una medicion desde el inicio
#define adcMeasureOnce (0x04) //Se realiza una medicion activando un trigger manual.

/*
 * Enumeración de triggers, en el ADC hay 8 triggers
 */

enum trigger{
    TR1, TR2, TR3, TR4, TR5, TR6, TR7, TR8
};

/*
 * Enumeración de canales, en el ADC hay 31 canales
 */

enum channel{//Buffers de conversion
    CH0, CH1, CH2, CH3, CH4, CH5, CH6,
    CH7, CH8, CH9, CH10, CH11, CH12, CH13,
    CH14, CH15, CH16, CH17, CH18, CH19, CH20,
    CH21, CH22, CH23, CH24, CH25, CH26, CH27,
    CH28, CH29, CH30, MAXCH=31,
};

/*
 * Enumeración de pins analogos, en el ADC hay de 0 a 18, y otros para funciones especificas de 19 a 23 y el a2
 */

enum analogPin{ // Pin analogos de la tarjeta
    AP0, AP1, AP2, AP3, AP4, AP5, AP6,
    AP7, AP8, AP9, AP10, AP11, AP12, AP13,
    AP14, AP15, AP16, AP17, AP18, APMAX = 18,
};

//Inicializa el modulo ADC.
extern void adcInit(void);
//Funcion que describe la resolución del reloj.
extern void adcClockR(uint32_t res);
//Funcion que describe el divisor de reloj
extern void adcClockD(uint32_t adcClkDiv);
//Configura el modo de conversión del ADC
extern void adcMode(uint32_t mode);
//Configura la cantidad de ciclos
extern void adcMSC(void);
/* Función que configura el canal de conversión. */
extern void adcConversion(uint32_t CMode);
//Configura el canal inicial y final de la secuencia de conversión.
extern void adcCanalInicial(uint32_t CH);
extern void adcCanalFinal(uint32_t CH);
/* Función que configura el pin analogo para un canal ADC. */
extern void adcConfigPin(uint32_t CH, uint32_t AP, uint32_t VRef);
/* Función que dispara la conversión ADC. */
extern void adcActivado(void);
/* Función que indica si hay una conversión en curso o no. */
extern _Bool adcOcupado(void);
/* Función que retorna el valor de la conversión ADC de un canal en específico. */
extern uint16_t adcResultado(uint16_t channel);

extern float ADC_GetTemperature(uint16_t CH);
#endif /* DRIVERS_ADC_H_ */
