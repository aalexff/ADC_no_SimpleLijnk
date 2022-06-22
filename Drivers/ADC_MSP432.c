/*
 * ADC.C
 *
 *  Created on: Jun 5, 2022
 *      Author: Administrador
 */

#include "ADC_MSP432.h"

/*
 * Function: adcInit
 * Preconditions: extern void adcInit() en ADC.h.
 * Overview: Configura e inicializa el modulo.
 * Input: Parámetros ninguno.
 * Output: Ninguno.
 *
 */

void adcInit(void){
    //El registro ADC14_CTL0[ON] Bits, activa el modulo en 1
    BITBAND_PERI(ADC_14->CTL0, ADC14_CTL0_ON_OFS) = 1;
    /*CTL0 = Control 0 Register */
}

/*
  * Function: adcClockD
  * Preconditions: Niguno
  * Overview: Establece si la conversion de muestreo multiple
  *           es de un flanco por subida o o un flanco para todos
  *           los muestreos.
  * Input: Niguno.
  * Output: Ninguno.
  *
  */

void adcMSC(void){
    BITBAND_PERI(ADC_14->CTL0, ADC14_CTL0_MSC_OFS  ) = 0;
}

    /*
     * Function: adcClockD
     * Preconditions: extern void adcClockD() en ADC.h.
     * Overview: Configura la división del reloj
     * Input: Parámetros uint32_t CLK_div.
     * Output: Ninguno.
     *
     */

void adcClockD(uint32_t adcClkDiv){
    //Aqui se configura el reloj.
    ADC_14 -> CTL0 |= adcClkDiv | ADC14_CTL0_SHT1__64 /*La division*/ | ADC14_CTL0_SHT0__192;
    /*ADC 14((ADC14_Type *) ADC14_BASE)   */
    BITBAND_PERI(ADC_14->CTL0, ADC14_CTL0_SHP_OFS) = 1;
}
    /*
     * Function: adcClockR
     * Preconditions: extern void adcClockR() en ADC.h.
     * Overview:
     *           Configura la resolución de la conversión ADC.
     * Input: Parámetros uint32_t RES.
     * Output: Ninguno.
     *
     */

void adcClockR(uint32_t res){
    //ADC14CTL1 configuramos la resolucion a la que va a trabajar el conversor
    ADC_14 -> CTL1 = res ;
    /*CTL1 = Control 1 Register */

}

/*
 * Function: adcConversion
 * Preconditions: adcInit(), extern void adcConversion en ADC.h.
 * Overview: Establece el modo de conversion
 * Input: uint32_t CMode.
 * Output: Ninguno.
 */

void adcConversion(uint32_t CMode){
    //Aqui configuramos  cual va a ser el modo de conversion mediante el registro ADC14CTL0
    ADC_14 -> CTL0 |= CMode;
}

/*
 * Function: canalFinal
 * Preconditions: adcInit(). Extern en ADC.h
 * Overview: Configura el canal final de una secuencia de conversión del ADC.
 * Input: uint32_t CH.
 * Output: Ninguno.
 */

void adcCanalFinal(uint32_t CH){
    //  Aqui elegimos cual es la direccion final del canal para el uso de modo secuencia
    BITBAND_PERI(ADC_14->MCTL[CH], ADC14_MCTLN_EOS_OFS) = 1;
}

/*
 * Function: ADC_Canal_Inicial
 * Preconditions: adcInit().
 * Overview: Configura el canal inicial de una secuencia de conversión del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 */

void adcCanalInicial(uint32_t CH){
    //Caso contrario, este serpa la direccion inicial del canal para el uso de modo secuencia
    ADC_14->CTL1 |= (CH<<ADC14_CTL1_CSTARTADD_OFS);
}

/*
 * Function: adcConfigPin
 * Preconditions: adcInit().
 * Overview: Configura el pin análogo para un canal ADC.
 * Input: uint32_t CH, uint32_t.
 * Output: None.
 *
 */

void adcConfigPin(uint32_t CH, uint32_t AP, uint32_t VRef){
    //Aqui se configura el pin analogo por donde tendremos la entrada del voltaje
    ADC_14 -> MCTL[CH] = VRef | AP;
}

/*
 * Function: ADC_Activar
 * Preconditions: adcInit().
 * Overview: Se inicia la conversión ADC.
 * Input: None.
 * Output: None.
 *
 */

void adcActivado(void){
    // Funcion bandera que activa la conversion y pone en alto la bandera de ocupado
    BITBAND_PERI(ADC_14->CTL0, ADC14_CTL0_ENC_OFS) = 1;
    BITBAND_PERI(ADC_14->CTL0, ADC14_CTL0_SC_OFS) = 1;
}

/*
 * Function: adcOcupado
 * Preconditions: adcInit().
 * Overview: Indica si hay una conversión en curso o no.
 * Input: None.
 * Output: Valor booleano.
 *
 */

_Bool adcOcupado(void){
    /*BAndera de ocupado, la cual se activa mientras se está realizando una conversion
     * (0) si no se está llevando a cabo una conversión.
     * (1) si hay una conversión en curso.               */
    return BITBAND_PERI(ADC_14->CTL0, ADC14_CTL0_BUSY_OFS);
}

/*
 * Function: adcResultado
 * Preconditions: ADC_init(), extern.
 * Overview: Retorna el valor de la conversión ADC para el canal "channel" dado.
 * Input: uint16_t channel.
 * Output: uint16_t con el valor de la conversión del canal "channel".
 *
 */
uint16_t adcResultado(uint16_t CH)
{
    /* Retorna el valor de la conversión ADC para el canal "channel" dado.
     * Los valores de las conversiones se almancenan en el arreglo MEM       */
    return ADC_14->MEM[CH];
}

//Esto hay que quitarlo al final
float ADC_GetTemperature(uint16_t CH)
{
    float   temp = 0.0;
    uint16_t cal30 = TLV->ADC14_REF2P5V_TS30C;
    uint16_t cal85 = TLV->ADC14_REF2P5V_TS85C;
    float calDiff = cal85 - cal30;
    adcActivado(); while(adcOcupado());
    temp =  ((((adcResultado(CH) - cal30) * 55) / calDiff) + 30.0f);
    return temp;
}

