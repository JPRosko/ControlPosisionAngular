#include "ADC.h"

long referencia(void)
{
    volatile long adc=0;
    P1DIR &= ~BIT7 ; // P1.7 será entrada
    ADC10CTL1 = INCH_7 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_1;  // Entrada P1.7
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON ;
    ADC10CTL0 |= ENC + ADC10SC;                                 // Sampling and conversion start
    __delay_cycles(500) ; // Tarda 13 ciclos (de 5MHz = 2.6 uS), MCLK = 1MHz/8, un ciclo serán 8 micros
    ADC10CTL0 &= ~ENC ;     ADC10CTL0 &= ~(ADC10ON) ; // Turning off (it is a two step process)
    adc=ADC10MEM;
    return(adc);   // tomar lectura
}


long medicion(void)
{
    volatile long adc=0;
    P1DIR &= ~BIT6 ; // P1.6 será entrada
    ADC10CTL1 = INCH_6 + ADC10SSEL_0 + ADC10DIV_0 + CONSEQ_1 ;  // Entrada P1.6
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON ;
    ADC10CTL0 |= ENC + ADC10SC;                                 // Sampling and conversion start
    __delay_cycles(500) ; // Tarda 13 ciclos (de 5MHz = 2.6 uS), MCLK = 1MHz/8, un ciclo serán 8 micros
    ADC10CTL0 &= ~ENC ;     ADC10CTL0 &= ~(ADC10ON) ; // Turning off (it is a two step process)
    adc=ADC10MEM;
    return(adc);   // tomar lectura
}
