#include"defines.h"

void initSW(void);
void configTIMER(void);


#define MUESTRAS 2

    /*   Asignacion de Pines   */
//    P1.7 será entrada Referencia
//    P1.6 será entrada Medicion
//    P2.4 será Salida PWM1 (Canal 1)
//    P2.1 será Salida PWM2 (Canal 2)

volatile float med;
volatile float ref;
float error=0;
int i=0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer

    configTIMER();

    initSW();

    P1DIR=0x00;

    while(1)
    {
        for(i=0;i<MUESTRAS;i++)
        {
            med+=0.26882*(float)medicion();
            ref+=0.26882*(float)referencia();
        }
        med/=MUESTRAS;
        ref/=MUESTRAS;

        error=ref - med;
        SCDifuso(ref,error);
    }
}

void configTIMER(void)
{
    if (CALBC1_1MHZ ==0xFF || CALDCO_16MHZ == 0xFF){while(1);}      // VLO --\                      |
    BCSCTL1 = CALBC1_16MHZ ;  DCOCTL = CALDCO_16MHZ;                //        o--o----- ACLK = LFXT |
    BCSCTL3 |= LFXT1S_2;                // LFXT1 = VLO              // Xtal--/    \                 |
    IFG1 &= ~OFIFG;                     // Clear OSCFault flag      //             o--- MCLK (CPU)  |
    BCSCTL2 |= SELM_0 + DIVM_0 + DIVS_0;// MCLK = DCO/8, SMCLK/1    //            /                 |
                                                                    // DCO ->----o----- SMCLK       |
}

void initSW(void)
{
    initPWM();
}
